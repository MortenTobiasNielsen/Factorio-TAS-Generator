local util = require("util")
local crash_site = require("crash-site")

local steps = require("steps")
local debug_state = require("goal")
local run = true

local step = 1
local step_reached = 0
local idle = 0
local mining = 0

local player
local player_selection
local player_position
local destination
local target_position
local target_inventory
local walking
local task
local task_category
local count
local item
local direction
local input
local output
local type
local rev
local duration = 0
local ticks_mining = 0
local idled = 0
local font_size = 0.15 --best guess estimate of fontsize for flying text

local pos_pos = false
local pos_neg = false
local neg_pos = false
local neg_neg = false


local drop_item
local drop_position

--recreate crash site
local on_player_created = function(event)
	if remote.interfaces["freeplay"] == nil then return end

	local player = game.get_player(event.player_index)
	local surface = player.surface
	local crashed_ship_items = remote.call("freeplay", "get_ship_items")
	local crashed_debris_items = remote.call("freeplay", "get_debris_items")
	util.insert_safe(player, global.created_items)

    surface.daytime = 0.7
    crash_site.create_crash_site(surface, {-5,-6}, util.copy(crashed_ship_items), util.copy(crashed_debris_items))
    util.remove_safe(player, crashed_ship_items)
    util.remove_safe(player, crashed_debris_items)
    player.get_main_inventory().sort_and_merge()
end

--Print message intended for viewers
local function msg(msg) 
    player.print(msg)
end

--Print debug message about what the tas is doing
local function debug(msg)
	if debug_state then
		player.print(msg)
        player.print(string.format(
            "Seconds: %s, tick: %s, player position [%d, %d]",
            game.tick / 60,
            game.tick,
            player.position.x,
            player.position.y
	))
	end
end

--Print warning in case of errors in tas programming
local function warning(msg)
    if debug_state then
		player.print(msg, {r=1, g=1}) -- print warnings in yellow
	end
end

local function save(task, nameOfSaveGame)
	if game.is_multiplayer() then
		debug(string.format("Task: %s, saving game as %s", task, nameOfSaveGame))
		game.server_save(nameOfSaveGame)
		return true
	end

	debug(string.format("Task: %s, saving game as _autosave-%s", task, nameOfSaveGame))
	game.auto_save(nameOfSaveGame)
	return true;
end

local function format_name(str)
	return str:gsub("^%l", string.upper):gsub("-", " ") --uppercase first letter and replace dashes with spaces
end

-- Check that the entity can be selected and is within reach
local function check_selection_reach()
	player.update_selected_entity(target_position)
	player_selection = player.selected

	if not player_selection then
		if not walking.walking then
			warning(string.format("Task: %s, Action: %s, Step: %d - %s: Cannot select entity", task[1], task[2], step, task_category))
		end

		return false
	end

	if not player.can_reach_entity(player_selection) then
		if not walking.walking then
			warning(string.format("Task: %s, Action: %s, Step: %d - %s: Cannot reach entity", task[1], task[2], step, task_category))
		end

		return false
	end

	return true
end

-- Check that it is possible to get the inventory of the entity
local function check_inventory() 
	target_inventory = player_selection.get_inventory(slot)

	if not target_inventory then
		if not walking.walking then
			warning(string.format("Task: %s, Action: %s, Step: %d - %s: Cannot get entity inventory", task[1], task[2], step, task_category))
		end

		return false
	end

	return true
end

-- Place an item from the character's inventory into an entity's inventory
-- Returns false on failure to prevent advancing step until within reach
-- It is possible to put 0 items if none are in the character's inventory
local function put()

	if not check_selection_reach() then
		return false;
	end

	if not check_inventory() then
		return false;
	end

	if amount == -1 then 
		amount = player.get_item_count(item)
	else 
		amount = math.min(player.get_item_count(item), amount)
	end

    if amount == 0 then
		warning(string.format("Task: %s, Action: %s, Step: %d - Put: Nothing to put", task[1], task[2], step))
		return true
	end

	amount = target_inventory.insert{name=item, count=amount}

	if amount == 0 then
		warning(string.format("Task: %s, Action: %s, Step: %d - Put: Entity is already full", task[1], task[2], step))
		return true
	end

	player.remove_item{name=item, count=amount}

	local text = string.format("-%d %s (%d)", amount, format_name(item), player.get_item_count(item)) --"-2 Iron plate (5)"
	local pos = {x = target_inventory.entity_owner.position.x + #text/2 * font_size, y = target_inventory.entity_owner.position.y }
	player.play_sound{path="utility/inventory_move"}
	player.create_local_flying_text{
		text=text, 
		position=pos}

	return true
end

-- Place an item into the character's inventory from an entity's inventory
-- Returns false on failure to prevent advancing step until within reach
-- It is possible to take 0 items if none are in the entity's inventory
local function take()

	if not check_selection_reach() then
		return false
	end

	if not check_inventory() then
		return false;
	end

	if amount == -1 then 
		amount = target_inventory.get_item_count(item)
	else 
		amount = math.min(target_inventory.get_item_count(item), amount)
	end

	if amount == 0 then
		warning(string.format("Task: %s, Action: %s, Step: %d - Take: Nothing to take", task[1], task[2], step))
		return true
	end
	
	amount = player.insert{name=item, count=amount}

	if amount == 0 then
		warning(string.format("Task: %s, Action: %s, Step: %d - Take: Nothing to take", task[1], task[2], step))
		return true
	end

	target_inventory.remove{name=item, count=amount}
	
	local text = string.format("+%d %s (%d)", amount, format_name(item), player.get_item_count(item)) --"+2 Iron plate (5)"
	local pos = {x = target_inventory.entity_owner.position.x + #text/2 * font_size, y = target_inventory.entity_owner.position.y }
	player.play_sound{path="utility/inventory_move"}
	player.create_local_flying_text{
		text=text,
		position=pos}

	return true
end

-- Handcraft one or more of a recipe
local function craft()
	amount = player.get_craftable_count(item);

	if amount > 0 then
		if count == -1 then
			player.begin_crafting{count = amount, recipe = item}
		else
			player.begin_crafting{count = math.min(count, amount), recipe = item}
		end

		return true
    else
        if(step > step_reached) then 
            warning(string.format("Task: %s, Action: %s, Step: %d - Craft: It is not possible to craft %s - Please check the script", task[1], task[2], step, item:gsub("-", " "):gsub("^%l", string.upper)))
            step_reached = step
		end
		
        return false
	end
end

local function item_is_tile(item)
	if item == "stone-brick"
	or item == "concrete"
    or item == "hazard-concrete"
    or item == "refined-concrete"
    or item == "refined-hazard-concrete"
    or item == "landfill" then
        return true
    end
    return false
end

local function tile_is_in_reach()	
	local x = player.position.x - target_position[1]
	local y = player.position.y - target_position[2]
	local dis = math.sqrt(x^2+y^2) --sqrt(a^2+b^2)=sqrt(c^2)
	return dis <= 10.25 -- It seems like 10.25 aligns best with the current walking algorithm
end

-- Creating buildings
local function build()

	if player.get_item_count(item) == 0 then
		if(step > step_reached) then
			if walking.walking == false then
				warning(string.format("Task: %s, Action: %s, Step: %d - Build: %s not available", task[1], task[2], step, item:gsub("-", " "):gsub("^%l", string.upper)))
				step_reached = step
			end
		end

		return false
	end

	if (item ~= "rail") then
		if item_is_tile(item) then
			if tile_is_in_reach() then
				if item == "stone-brick" then 
					player.surface.set_tiles({{position = target_position, name = "stone-path"}})
				elseif (item == "hazard-concrete") or (item == "refined-hazard-concrete") then
					player.surface.set_tiles({{position = target_position, name = item.."-left"}})
				else
					player.surface.set_tiles({{position = target_position, name = item}})
				end
	
				if(item == "landfill") then
					player.surface.play_sound{path="tile-build-small/landfill", position=target_position}
				else
					player.surface.play_sound{path="tile-build-small/concrete", position=target_position}
				end
	
				player.remove_item({name = item, count = 1})
				return true
				
			elseif not walking.walking then
				warning(string.format("Task: %s, Action: %s, Step: %d - Build: %s not in reach", task[1], task[2], step, item:gsub("-", " "):gsub("^%l", string.upper)))
			end

			return false

		elseif player.can_place_entity{name = item, position = target_position, direction = direction} then
			if player.surface.can_fast_replace{name = item, position = target_position, direction = direction, force = "player"} then
				if player.surface.create_entity{name = item, position = target_position, direction = direction, force="player", fast_replace=true, player=player, raise_built = true} then
					step = step - 1
					player.remove_item({name = item, count = 1})
					return true
				end
			else
				if player.surface.create_entity{name = item, position = target_position, direction = direction, force="player", raise_built = true} then
					player.remove_item({name = item, count = 1})
					return true
				end
			end
	
		else 
			if not walking.walking then
				warning(string.format("Task: %s, Action: %s, Step: %d - Build: %s cannot be placed", task[1], task[2], step, item:gsub("-", " "):gsub("^%l", string.upper)))
			end
	
			return false
		end
	else
		if player.can_place_entity{name = "straight-rail", position = target_position, direction = direction} then
			if player.surface.can_fast_replace{name = "straight-rail", position = target_position, direction = direction, force = "player"} then
				if player.surface.create_entity{name = "straight-rail", position = target_position, direction = direction, force="player", fast_replace=true, player=player, raise_built = true} then
					step = step - 1
					player.remove_item({name = item, count = 1})
					return true
				end
			else
				if player.surface.create_entity{name = "straight-rail", position = target_position, direction = direction, force="player", raise_built = true} then
					player.remove_item({name = item, count = 1})
					return true
				end
			end
	
		else 
			if not walking.walking then
				warning(string.format("Task: %s, Action: %s, Step: %d - Build: %s cannot be placed", task[1], task[2], step, item:gsub("-", " "):gsub("^%l", string.upper)))
			end
	
			return false
		end
	end
end

local function walk_pos_pos()
	if player_position.x > destination.x then
		if player_position.y > destination.y then
			return {walking = true, direction = defines.direction.northwest}
			
		else
			return {walking = true, direction = defines.direction.west}
		end
	else
		if player_position.y > destination.y then
			return {walking = true, direction = defines.direction.north}
		else
			return {walking = false, direction = defines.direction.north}	
		end
	end

	return {walking = false, direction = defines.direction.north}	
end

local function walk_pos_neg()
	if player_position.x > destination.x then
		if player_position.y < destination.y then
			return {walking = true, direction = defines.direction.southwest}
		else
			return {walking = true, direction = defines.direction.west}
		end
	else
		if player_position.y < destination.y then
			return {walking = true, direction = defines.direction.south}
		else
			return {walking = false, direction = defines.direction.north}	
		end
	end

	return {walking = false, direction = defines.direction.north}	
end

local function walk_neg_pos()
	if player_position.x < destination.x then
		if player_position.y > destination.y then
			return {walking = true, direction = defines.direction.northeast}
		else
			return {walking = true, direction = defines.direction.east}
		end
	else
		if player_position.y > destination.y then
			return {walking = true, direction = defines.direction.north}
		else
			return {walking = false, direction = defines.direction.north}	
		end
	end

	return {walking = false, direction = defines.direction.north}	
end

local function walk_neg_neg()
	if player_position.x < destination.x then
		if player_position.y < destination.y then
			return {walking = true, direction = defines.direction.southeast}
		else
			return {walking = true, direction = defines.direction.east}
		end
	else
		if player_position.y < destination.y then
			return {walking = true, direction = defines.direction.south}
		else
			return {walking = false, direction = defines.direction.north}	
		end
	end

	return {walking = false, direction = defines.direction.north}	 
end

local function walk()
	if pos_pos then
		return walk_pos_pos()
	elseif pos_neg then
		return walk_pos_neg()
	elseif neg_pos then
		return walk_neg_pos()
	elseif neg_neg then
		return walk_neg_neg()
	end

	return {walking = false, direction = defines.direction.north}	 
end

local function find_walking_pattern() 
	if (player_position.x - destination.x >= 0) then
		if (player_position.y - destination.y >= 0) then
			pos_pos = true
			pos_neg = false
			neg_pos = false
			neg_neg = false
		elseif (player_position.y - destination.y < 0) then
			pos_neg = true
			pos_pos = false
			neg_pos = false
			neg_neg = false
		end
	else
		if (player_position.y - destination.y >= 0) then
			neg_pos = true
			pos_pos = false
			pos_neg = false
			neg_neg = false
		elseif (player_position.y - destination.y < 0) then
			neg_neg = true
			pos_pos = false
			pos_neg = false
			neg_pos = false
		end
	end
end

local function rotate()
	local r = false
	if not check_selection_reach() then
		return false;
	end

	if rev then
		r = player_selection.rotate({reverse = true})
	else 
		r = player_selection.rotate({reverse = false})
	end 

	if r then player.play_sound{path="utility/rotated_small"} end
	
	return true
end

local function recipe()

	if not check_selection_reach() then
		return false
	end

	local items_returned = player_selection.set_recipe(item)

	for name, count in pairs (items_returned) do
		player.insert{name = name, count = count}
	end

	return true
end

local function tech()
	player.force.add_research(item)
    msg(string.format("Add research %s", item))
	return true
end

local function pause()
	game.tick_paused = true
	return true
end

-- Set the gameplay speed. 1 is standard speed
local function speed(speed)
	game.speed = speed
    msg(string.format("Changed game speed to %s", speed))
	return true
end

-- Set the inventory slot space on chests (and probably other items, which are untested)
-- Returns false on failure to prevent advancing step until within reach
local function limit()
	if not check_selection_reach() then
		return false
	end
	
	if not check_inventory() then
		return false
	end

	-- Setting set_bar to 1 completely limits all slots, so it's off by one
	target_inventory.set_bar(amount+1)
	return true
end

local function priority()
	
	if not check_selection_reach() then
		return false
	end

	player_selection.splitter_input_priority = input
	player_selection.splitter_output_priority = output

	return true
end

local function filter() 

	if not check_selection_reach() then
		return false
	end

	if type == "splitter" then
		if item == "none" then
			player_selection.splitter_filter = nil
		else
			player_selection.splitter_filter = item
		end

		return true
	end

	if item == "none" then
		player_selection.set_filter(slot, nil)
	else
		player_selection.set_filter(slot, item)
	end

	return true
end

-- Drop items on the ground (like pressing the 'z' key)
local function drop()

	if player.can_place_entity{name = drop_item, position = drop_position} then
		player.surface.create_entity{name = "item-on-ground",
								stack = {
									name = drop_item,
									count = 1,
								},
								position = drop_position,
								force = "player",
								spill = true
								}
		return true
	end	

	return false
end

-- Manually launch the rocket
-- Returns false on failure to prevent advancing step until the launch succeeds
local function launch()
	if not check_selection_reach() then
		return false
	end

	return player_selection.launch_rocket()
end

-- Routing function to perform one of the many available steps
-- True: Indicates the calling function should advance the step. 
-- False: Indicates the calling function should not advance step.
local function doStep(steps)
	if steps[2] == "craft" then
        task_category = "Craft"
        task = steps[1]
		count = steps[3]
		item = steps[4]

		return craft()

	elseif steps[2] == "build" then
        task_category = "Build"
        task = steps[1]
		target_position = steps[3]
		item = steps[4]
		direction = steps[5]

		return build()

	elseif steps[2] == "take" then
        task_category = "Take"
        task = steps[1]
		target_position = steps[3]
		item = steps[4]
		amount = steps[5]
		slot = steps[6]

		return take()

	elseif steps[2] == "put" then
        task_category = "Put"
        task = steps[1]
		target_position = steps[3]
		item = steps[4]
		amount = steps[5]
		slot = steps[6]

		return put()

	elseif steps[2] == "rotate" then
        task_category = "Rotate"
        task = steps[1]
		target_position = steps[3]
		rev = steps[4]

		return rotate()

	elseif steps[2] == "tech" then
        task_category = "Tech"
        task = steps[1]
		item = steps[3]

		return tech()

	elseif steps[2] == "recipe" then
        task_category = "Recipe"
        task = steps[1]
		target_position = steps[3]
		item = steps[4]

		return recipe()

	elseif steps[2] == "limit" then
        task_category = "limit"
        task = steps[1]
		target_position = steps[3]
		amount = steps[4]
		slot = steps[5]
		
		return limit()

	elseif steps[2] == "priority" then
        task_category = "priority"
        task = steps[1]
		target_position = steps[3]
		input = steps[4]
		output = steps[5]

		return priority()

	elseif steps[2] == "filter" then
        task_category = "filter"
        task = steps[1]
		target_position = steps[3]
		item = steps[4]
		slot = steps[5]
		type = steps[6]

		return filter()

    elseif steps[2] == "drop" then
        task = steps[1]
		drop_position = steps[3]
		drop_item = steps[4]
		return drop()

	elseif steps[2] == "pick" then
		player.picking_state = true
		return true

	elseif steps[2] == "idle" then
		idle = steps[3]
		return true
	
	elseif steps[2] == "launch" then
		task_category = "launch"
        task = steps[1]
		target_position = steps[3]

		return launch()
	end
end

-- Main per-tick event handler
script.on_event(defines.events.on_tick, function(event)
	if not run then return end
    if not player then 
		player = game.players[1]
		player.surface.always_day=true
		player_position = player.position
		destination = {x = player_position.x, y = player_position.y}
		player.force.research_queue_enabled = true
		walking = {walking = false, direction = defines.direction.north}

	elseif player.character ~= nil then
		player_position = player.position

		if steps[step] == nil or steps[step][1] == "break" then
			debug(string.format("(%.2f, %.2f) Complete after %f seconds (%d ticks)", player_position.x, player_position.y, player.online_time / 60, player.online_time))		
			debug_state = false
			return
		end

		if (steps[step][2] == "pause") then
			pause()
			debug("Script paused")
			debug(string.format("(%.2f, %.2f) Complete after %f seconds (%d ticks)", player_position.x, player_position.y, player.online_time / 60, player.online_time))	
			debug_state = false
			return
		end

		if (steps[step][2] == "stop") then
			speed(steps[step][3])
			debug(string.format("Script stopped - Game speed: %d", steps[step][3]))
			debug(string.format("(%.2f, %.2f) Complete after %f seconds (%d ticks)", player_position.x, player_position.y, player.online_time / 60, player.online_time))	
			debug_state = false
			return
		end

		if (steps[step][2] == "speed") then
			debug(string.format("Task: %s, Action: %s, Step: %s - Game speed: %d", steps[step][1][1], steps[step][1][2], step, steps[step][3]))
			speed(steps[step][3])
			step = step + 1
		end

		if steps[step][2] == "save" then
			save(steps[step][1][1], steps[step][3])
			step = step + 1
		end

		walking = walk()
		if walking.walking == false then
			if idle > 0 then
				idle = idle - 1
				idled = idled + 1

				debug(string.format("Task: %s, Action: %s, Step: %s - idled for %d", steps[step][1][1]-1, steps[step][1][2], step-1, idled))

				if idle == 0 then
					idled = 0
				end
			elseif steps[step][2] == "walk" then
				destination = {x = steps[step][3][1], y = steps[step][3][2]}

				find_walking_pattern()
				walking = walk()

				step = step + 1

			elseif steps[step][2] == "mine" then
				
				player.update_selected_entity(steps[step][3])

				player.mining_state = {mining = true, position = steps[step][3]}

				duration = steps[step][4]

				ticks_mining = ticks_mining + 1

				if ticks_mining >= duration then
					player.mining_state = {mining = false, position = steps[step][3]}
					step = step + 1
					mining = 0
					ticks_mining = 0
				end

				mining = mining + 1
				if mining > 5 then
					if player.character_mining_progress == 0 then
						warning(string.format("Task: %s, Action: %s, Step: %s - Mine: Cannot reach resource", steps[step][1][1], steps[step][1][2], step))
						debug_state = false
					else
						mining = 0
					end
				end
				
			elseif doStep(steps[step]) then
				-- Do step while standing still
				step = step + 1

			end
		else
			if steps[step][2] ~= "walk" and steps[step][2] ~= "mine" and steps[step][2] ~= "idle" and steps[step][2] ~= "pick" then
				if doStep(steps[step]) then
					
					-- Do step while walking
					step = step + 1
				end
			end
		end	

		player.walking_state = walking
	end	
end)

local function mining_event_replace(event, item_name, amount)
	local count = event.buffer.get_item_count(item_name)
	if count < amount then
		event.buffer.insert({name=item_name, count=amount-count})
	elseif count > amount then
		event.buffer.remove({name=item_name, count=count-amount})
	end --on correct amount do nothing
end

script.on_event(defines.events.on_player_mined_entity, function(event)

	if (steps[step][1] == "break" or steps[step][2] == "stop") then
		return
	end

	if event.entity.name == "rock-huge" then
		mining_event_replace(event, "coal", 47)
		mining_event_replace(event, "stone", 47)
	end

	if event.entity.name == "rock-big" then
		-- do nothing, big rocks are always 20 stone
	end

	if event.entity.name == "sand-rock-big" then
		mining_event_replace(event, "stone", 24)
	end

	step = step + 1
	mining = 0
	ticks_mining = 0
end)

-- Skips the freeplay intro
script.on_event(defines.events.on_game_created_from_scenario, function()

	remote.call("freeplay", "set_skip_intro", true)

end)

--release tas on writing "release" in console
script.on_event(defines.events.on_console_chat, function(event)
	if event.message and event.message == "release" then
		run = false
	end
end)

-- Triggered on script built
script.on_event(defines.events.script_raised_built, function(event)
	local entity = event.entity
	entity.create_build_effect_smoke()
	entity.surface.play_sound{path="entity-build/"..entity.prototype.name, position=entity.position}
end)

--modsetting names are stored in a global array for all mods, so each setting value needs to be unique among all mods
local settings_short = "DunRaider-quickbar-"
local function split_string(str)
	if str == nil then return end
	local t = {}
	for s in string.gmatch(str, "([^,]+)") do table.insert(t, s) end
	return t
end

--seperate functions in case we want it to trigger on other events
local function set_quick_bar(event)
	local player = game.players[event.player_index]
	for i = 1, 10 do 
		local set = split_string(settings.global[settings_short..i].value)
		for key,val in pairs(set) do
			player.set_quick_bar_slot((i-1)*10 + key, string.sub(val, 7, -2)) -- removes "[item=" and "]"
		end
	end
end

script.on_event(defines.events.on_player_joined_game, function(event)
	set_quick_bar(event)
end)

script.on_event(defines.events.on_player_created, function(event)
	set_quick_bar(event)
	on_player_created(event)
end)


script.on_init(function()
    local freeplay = remote.interfaces["freeplay"]
    if freeplay then
		if freeplay["set_skip_intro"] then remote.call("freeplay", "set_skip_intro", true) end -- Disable freeplay popup-message
        if freeplay["set_disable_crashsite"] then remote.call("freeplay", "set_disable_crashsite", true) end --Disable crashsite
    end
end)