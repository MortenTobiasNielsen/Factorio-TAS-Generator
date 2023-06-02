require("variables") --gets GOAL

--Config  strings
local anyp = "Any%"
local gotlap = "Getting On Track Like A Pro"
local steelaxe = "Steel Axe"

--Constants 
local steelaxe_research = "steel-axe"
local gotlap_filter = {{filter="name", name="locomotive"}}

---Prints game end info and raise victory event
---@param message string
local function game_end_simple(message)
    if global.goal and global.goal.completed then return end
    global.goal = {completed = true}
    game.print(
        {
            "goal.end_message",
            message,
            math.floor(game.tick / (60*60*60)),
            math.floor((game.tick % (60*60*60)) / (60*60)),
            math.floor((game.tick % (60*60)) / (60)),
            math.floor((game.tick % 60) / 60 * 1000),
            game.tick
        }
    )
end

---Display victory gui
---@param message string
local function game_end(message)
    if global.goal and global.goal.completed then return end
    game_end_simple(message)
    game.set_game_state{game_finished = true, player_won = true, "free-play", can_continue = true}
end

---Event handler for any%
---@param event EventData.on_rocket_launched
local function handle_rocket_launch_event(event)
    if GOAL == anyp then
        game_end_simple(anyp)
    end
end

---Event handler for research event that filters steelaxe
---@param event EventData.on_research_finished
local function handle_research_finished_event(event)
    if GOAL == steelaxe and event.research.name == steelaxe_research then
        game_end(steelaxe)
    end
end

---Event handler for GOTLAP
---@param event EventData.script_raised_built | EventData.on_built_entity | EventData.on_robot_built_entity
local function handle_entity_built_event(event)
    if GOAL == gotlap then
        game_end(gotlap)
    end
end

---Register appropiate event handlers based on configuration
local function register_event()
    if GOAL == anyp then
        script.on_event(defines.events.on_rocket_launched, handle_rocket_launch_event)
    elseif GOAL == steelaxe then
        script.on_event(defines.events.on_research_finished, handle_research_finished_event)
    elseif GOAL ==  gotlap then
        script.on_event(defines.events.script_raised_built, handle_entity_built_event, gotlap_filter)
        script.on_event(defines.events.on_built_entity, handle_entity_built_event, gotlap_filter)
        --script.on_event(defines.events.on_robot_built_entity, gotlap, gotlap_filter) --not needed as robots are not implemented
    else
        error("Unknown Goal configuration")
    end
end

register_event()
