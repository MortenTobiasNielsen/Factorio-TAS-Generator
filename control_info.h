#pragma once
#include <string>

std::string info = { R"info(
	"version": "0.0.1",
	"title": "EZRaider TAS helper",
	"author": "DunRaider",
	"factorio_version": "1.0",
	"contact": "",
	"description": "This run has been made with the help of EZRaiderz TAS helper"
})info"
};

std::string control_lua = R"control_lua(
require "util"
local task = require("tasks")
local walk_proximity = 0.1
local debug_state = true

local state = 1
local state_reached = 0
local idle = 0

local player
local player_selection
local position
local destination
local target_inventory
local walking
local step
local count
local item
local direction
local input
local output
local type

local drop_item
local drop_position

local function debug(msg)
	if debug_state then
		player.print(msg)
	end
end

-- Check that the entity can be selected and is within reach
local function check_selection_reach()
	player.update_selected_entity(position)
	player_selection = player.selected

	if not player_selection then
		if not walking.walking then
			debug(string.format("Step %d - %s: Cannot select entity", state, step))
		end

		return false
	end

	if not player.can_reach_entity(player_selection) then
		if not walking.walking then
			debug(string.format("Step %d - %s: Cannot reach entity", state, step))
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
			debug(string.format("Step: %d - %s: Cannot get entity inventory", state, step))
		end

		return false
	end

	return true
end

-- Place an item from the character's inventory into an entity's inventory
-- Returns false on failure to prevent advancing state until within reach
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
		debug(string.format("Step %d - Put: Nothing to put", state))
		return true
	end

	amount = target_inventory.insert{name=item, count=amount}

	if amount == 0 then
		debug(string.format("Step %d - Put: Entity is already full", state))
		return true
	end

	player.remove_item{name=item, count=amount}
	return true
end

-- Place an item into the character's inventory from an entity's inventory
-- Returns false on failure to prevent advancing state until within reach
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
		debug(string.format("Step %d - Take: Nothing to take", state))
		return true
	end

	amount = player.insert{name=item, count=amount}

	if amount == 0 then
		debug(string.format("Step %d - Take: Nothing to take", state))
		return true
	end

	target_inventory.remove{name=item, count=amount}

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
        if(state > state_reached) then 
            debug(string.format("Step %d - Craft: It is not possible to craft %s - Please check the script", state, item:gsub("-", " "):gsub("^%l", string.upper)))
            state_reached = state
		end
		
        return false
	end
end

-- Creating buildings
local function build()

	if player.get_item_count(item) == 0 then
		if(state > state_reached) then 
			debug(string.format("Step %d - Build: %s not available", state, item:gsub("-", " "):gsub("^%l", string.upper)))
			state_reached = state
		end

		return false
	end

	if player.can_place_entity{name = item, position = position} then
		if player.surface.can_fast_replace{name = item, position = position, direction = direction, force = "player"} then
			if player.surface.create_entity{name = item, position = position, direction = direction, force="player", fast_replace=true, player=player} then
				state = state - 1
				player.remove_item({name = item, count = 1})
				return true
			end
		else
			if player.surface.create_entity{name = item, position = position, direction = direction, force="player"} then
				player.remove_item({name = item, count = 1})
				return true
			end
		end

	else 
		if not walking.walking then
			debug(string.format("Step %d - Build: %s cannot be placed", state, item:gsub("-", " "):gsub("^%l", string.upper)))
		end

		return false
	end
end

local function walk(delta_x, delta_y)
	if delta_x > walk_proximity then
		-- Easterly
		if delta_y > walk_proximity then
			return {walking = true, direction = defines.direction.southeast}
		elseif delta_y < -walk_proximity then
			return {walking = true, direction = defines.direction.northeast}
		else
			return {walking = true, direction = defines.direction.east}
		end
	elseif delta_x < -walk_proximity then
		-- Westerly
		if delta_y > walk_proximity then
			return {walking = true, direction = defines.direction.southwest}
		elseif delta_y < -walk_proximity then
			return {walking = true, direction = defines.direction.northwest}
		else
			return {walking = true, direction = defines.direction.west}
		end
	else
		-- Vertically
		if delta_y > walk_proximity then
			return {walking = true, direction = defines.direction.south}
		elseif delta_y < -walk_proximity then
			return {walking = true, direction = defines.direction.north}
		else
			return {walking = false, direction = defines.direction.north}
		end
	end
end

local function rotate()

	if not check_selection_reach() then
		return false;
	end

	player_selection.rotate()
	
	return true
end

local function recipe()

	if not check_selection_reach() then
		return false
	end

	player_selection.set_recipe(item)

	return true
end

local function tech()
	player.force.add_research(item)
	return true
end

-- Set the gameplay speed. 1 is standard speed
local function speed(speed)
	game.speed = speed
	return true
end

-- Set the inventory slot space on chests (and probably other items, which are untested)
-- Returns false on failure to prevent advancing state until within reach
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
-- Returns false on failure to prevent advancing state until the launch succeeds
local function launch()
	if not check_selection_reach() then
		return false
	end

	return player_selection.launch_rocket()
end

-- Routing function to perform one of the many available tasks
-- True: Indicates the calling function should advance the state. 
-- False: Indicates the calling function should not advance state.
local function doTask(task)
	if task[1] == "craft" then
		step = "Craft"
		count = task[2]
		item = task[3]

		return craft()

	elseif task[1] == "build" then
		step = "Build"
		position = task[2]
		item = task[3]
		direction = task[4]

		return build()

	elseif task[1] == "take" then
		step = "Take"
		position = task[2]
		item = task[3]
		amount = task[4]
		slot = task[5]

		return take()

	elseif task[1] == "put" then
		step = "Put"
		position = task[2]
		item = task[3]
		amount = task[4]
		slot = task[5]

		return put(task[2], task[3], task[4], task[5])

	elseif task[1] == "rotate" then
		step = "Rotate"
		position = task[2]

		return rotate()

	elseif task[1] == "tech" then
		step = "Tech"
		item = task[2]

		return tech()

	elseif task[1] == "recipe" then
		step = "Recipe"
		position = task[2]
		item = task[3]

		return recipe()

	elseif task[1] == "limit" then
		step = "limit"
		position = task[2]
		amount = task[3]
		slot = task[4]
		
		return limit()

	elseif task[1] == "priority" then
		step = "priority"
		position = task[2]
		input = task[3]
		output = task[4]

		return priority()

	elseif task[1] == "filter" then
		step = "filter"
		position = task[2]
		item = task[3]
		slot = task[4]
		type = task[5]

		return filter()

	elseif task[1] == "drop" then
		drop_position = task[2]
		drop_item = task[3]
		return drop()

	elseif task[1] == "pick" then
		player.picking_state = true
		return true

	elseif task[1] == "idle" then
		idle = task[2]
		return true
	
	elseif task[1] == "launch" then
		position = task[2]

		return launch()
	end
end

-- Main per-tick event handler
script.on_event(defines.events.on_tick, function(event)

    if not player then 
		player = game.players[1]
		position = player.position
		destination = {x = position.x, y = position.y}
		player.force.research_queue_enabled = true
	end

	position = player.position

	if task[state] == nil or task[state][1] == "break" then
		debug(string.format("(%.2f, %.2f) Complete after %f seconds (%d ticks)", position.x, position.y, player.online_time / 60, player.online_time))		
		debug_state = false
		return
	end

	if (task[state][1] == "stop") then
		speed(task[state][2])
		debug(string.format("Script stopped - Game speed: %d", task[state][2]))
		debug(string.format("(%.2f, %.2f) Complete after %f seconds (%d ticks)", position.x, position.y, player.online_time / 60, player.online_time))	
		debug_state = false
		return
	end

	if (task[state][1] == "speed") then
		debug(string.format("Game speed: %d", task[state][2]))
		speed(task[state][2])
		state = state + 1
	end

	-- primary movement
	walking = walk(destination.x - position.x, destination.y - position.y)
	if walking.walking == false then

		if idle > 0 then
			idle = idle - 1
		elseif task[state][1] == "walk" then
			destination = {x = task[state][2][1], y = task[state][2][2]}
			walking = walk(destination.x - position.x, destination.y - position.y)
			state = state + 1

		elseif task[state][1] == "mine" then
			player.update_selected_entity(task[state][2])
			player.mining_state = {mining = true, position = task[state][2]}

		elseif doTask(task[state]) then
			-- Do task while standing still
			state = state + 1

		end
	else
		if task[state][1] ~= "walk" and task[state][1] ~= "mine" and task[state][1] ~= "idle" and task[state][1] ~= "pick" then
			if doTask(task[state]) then
				-- Do task while walking
				state = state + 1
			end
		end
	end

	player.walking_state = walking
end)

script.on_event(defines.events.on_player_mined_entity, function(event)

	if (task[state][1] == "break" or task[state][1] == "stop") then
		return
	end

	if event.entity.name == "rock-huge" then
		event.buffer.clear()
		player.insert{name="coal", count=47}
		player.insert{name="stone", count=47}
	end

	if event.entity.name == "rock-big" then
		event.buffer.clear()
		player.insert{name="stone", count=20}
	end

	if event.entity.name == "sand-rock-big" then
		event.buffer.clear()
		player.insert{name="stone", count=20}
	end	

	state = state + 1
end)

-- Skips the freeplay intro
script.on_event(defines.events.on_game_created_from_scenario, function()

	remote.call("freeplay", "set_skip_intro", true)

end)

-- Skips the freeplay intro
script.on_event(defines.events.on_research_finished, function(event)

	if (event.research.name == "steel-axe") then
		local seconds = player.online_time / 60
		local minutes = math.floor(player.online_time / 60 / 60)
		local seconds_remainder = seconds - (minutes * 60) 

		debug(string.format("Contrats %s on reaching the end of your Steel Axe run - you completed it in %f seconds (%d min %f seconds) (%d ticks)", player.name, seconds, minutes, seconds_remainder , player.online_time))		
		debug_state = false
	end
	

end)

)control_lua";