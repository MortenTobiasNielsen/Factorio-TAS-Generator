require("variables") --gets GOAL

--Config  strings
local anyp = "Any%"
local gotlap = "Getting On Track Like A Pro"
local steelaxe = "Steel Axe"
local supply = "Supply challenge"

--Constants 
local steelaxe_research = "steel-axe"
local gotlap_filter = {{filter="name", name="locomotive"}}

local human_wr_times = {
    [anyp] = {
        final = {1,22,59.8},
        research = {
            ["automation"] = {0,6,36.4,},
            ["electronics"] = {0,11,53.9},
            ["fast-inserter"] = {0,14,24.0},
            ["logistics"] = {0,16,03.7},
            ["logistic-science-pack"] = {0,18,52.8},
            ["steel-processing"] = {0,19,30.9},
            ["steel-axe"] = {0,21,10.5},
            ["automation-2"] = {0,21,33.5},
            ["advanced-material-processing"] = {0,22,50.2},
            ["lab-research-speed-1"] = {0,24,24.2},
            ["lab-research-speed-2"] = {0,27,00.3},
            ["engine"] = {0,27,32.5},
            ["fluid-handling"] = {0,27,52.5},
            ["oil-processing"] = {0,28,57.0},
            ["plastics"] = {0,30,54.6},
            ["advanced-electronics"] = {0,32,34.7},
            ["sulfur-processing"] = {0,34,28.1},
            ["chemical-science-pack"] = {0,34,49.5},
            ["battery"] = {0,36,49.4},
            ["modules"] = {0,37,51.7},
            ["speed-module"] = {0,38,22.3},
            ["productivity-module"] = {0,38,52.8},
            ["advanced-oil-processing"] = {0,39,39.7},
            ["lubricant"] = {0,40,11.2},
            ["electric-engine"] = {0,40,41.4},
            ["robotics"] = {0,41,28.3},
            ["construction-robotics"] = {0,42,29.4},
            ["worker-robot-speed-1"] = {0,43,00.0},
            ["worker-robot-speed-2"] = {0,44,02.3},
            ["low-density-structure"] = {0,48,49.7},
            ["circuit-network"] = {0,49,19.0},
            ["logistics-2"] = {0,51,16.8},
            ["advanced-electronics-2"] = {0,54,19.8},
            ["railway"] = {0,55,09.6},
            ["advanced-material-processing-2"] = {0,57,37.1},
            ["production-science-pack"] = {0,58,40.1},
            ["utility-science-pack"] = {0,59,39.1},
            ["flammables"] = {1,00,08.5},
            ["concrete"] = {1,02,33.7},
            ["productivity-module-2"] = {1,03,13.6},
            ["speed-module-2"] = {1,03,54.2},
            ["rocket-fuel"] = {1,06,34.5},
            ["effect-transmission"] = {1,07,02.0},
            ["rocket-control-unit"] = {1,10,34.4},
            ["productivity-module-3"] = {1,12,48.0},
            ["speed-module-3"] = {1,14,47.7},
            ["rocket-silo"] = {1,21,00.7},
        },
    },
    [gotlap] = {
        final = {0,19,49.7},
        research = {
            ["automation"] = {0,4,50.9},
            ["logistic-science-pack"] = {0,9,50.1},
            ["steel-processing"] = {0,11,01.1},
            ["logistics"] = {0,11,40.8},
            ["engine"] = {0,13,35.6},
            ["logistics-2"] = {0,18,10.2},
            ["railway"] = {0,19,39.5},
        },
    },
    [steelaxe] = {
        final = {0,8,31.6},
        research = {
            ["automation"] = {0,4,09.6},
            ["steel-processing"] = {0,6,23.5},
            ["steel-axe"] = {0,8,31.6},
        },
    },
    [supply] = {
        final = {0,46,38.7},
        research = {
            ["automation"] = {0,11,09.6},
            ["logistics"] = {0,18,44.4},
            ["electronics"] = {0,22,43.1},
            ["fast-inserter"] = {0,25,33.9},
            ["logistic-science-pack"] = {0,29,24.1},
            ["steel-processing"] = {0,29,59.8},
            ["military"] = {0,30,16.3},
            ["stone-wall"] = {0,30,24.2},
            ["military-2"] = {0,30,46.6},
            ["automation-2"] = {0,31,15.6},
            ["engine"] = {0,32,27.4},
            ["fluid-handling"] = {0,33,02.1},
            ["oil-processing"] = {0,34,29.5},
            ["plastics"] = {0,36,56.2},
            ["advanced-electronics"] = {0,38,39.6},
            ["sulfur-processing"] = {0,40,36.2},
            ["military-science-pack"] = {0,40,46.8},
            ["chemical-science-pack"] = {0,41,10.1},
            ["logistics-2"] = {0,43,22.6},
        },
    }
}

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

---Builds a custom gui showing the Victory screen but with research times compared to human wr-times instead of kills
---@param message string
local function game_end_advanced(message)
    local player = game.players[1]
    local screen = player.gui.screen
    local main_frame = screen.add{ type = "frame", direction = "vertical", }
    global.tas_goal_control = {main = main_frame}
    do
        local title_bar = main_frame.add{ type = "flow", direction = "horizontal", name = "title_bar", }
        title_bar.drag_target = main_frame
        --title_bar.add{ type = "sprite", sprite = "t-tas-helper_icon"} --todo
        title_bar.add{ type = "label", style = "frame_title", caption = "Game finished", ignored_by_interaction = true, }
        local draggable_space = title_bar.add{ type = "empty-widget", style = "draggable_space_header", ignored_by_interaction = true, }

        draggable_space.style.horizontally_stretchable = true
        draggable_space.style.vertically_stretchable = true
        draggable_space.style.height = 24
        draggable_space.style.right_margin = 4
    end

    local inner_frame = main_frame.add{ type = "frame", direction = "vertical", style="inside_shallow_frame", }

    do
        local sub_header = inner_frame.add{ type = "frame", style="finished_game_subheader_frame", }
        local sub_header_flow = sub_header.add{ type = "flow", direction = "vertical", name = "head_time_flow",}
        sub_header_flow.add{ type = "label", caption = message .. " achieved", }
        sub_header.style.horizontally_stretchable = true
    end

    local scroll_flow = inner_frame.add{ type = "scroll-pane", direction = "vertical", style="scroll_pane_under_subheader"}
    scroll_flow.style.maximal_height = 500
    local table_frame = scroll_flow.add{ type = "frame", direction = "vertical", style = "b_inner_frame"}

    local top_table = table_frame.add{ type = "table", style = "finished_game_table", column_count = 3,}

    local function int_to_string(i)
        return i < 10 and string.format("0%d",i) or string.format("%d",i)
    end

    do
        local top_table_label = top_table.add{ type = "label", caption = "Time played", style = "caption_label"}
        local final_compare_time = human_wr_times[GOAL].final
        local compare_time = final_compare_time[1] * 60 * 60 *60 + final_compare_time[2] * 60 * 60 + final_compare_time[3] * 60
        local time = game.tick
        local ticks = math.abs(time - compare_time)
        top_table.add{ type = "label", style = "bold_label", caption = string.format("%d:%s:%s.%d ",
            time / (60*60*60),
            int_to_string((time % (60*60*60)) / (60*60)),
            int_to_string((time % (60*60)) / (60)),
            (time % 60) / 60 * 10)}
        top_table.add{ type = "label", style = time < compare_time and "bold_green_label" or "bold_red_label", caption = string.format(
                "%s%s:%s.%d",
                time < compare_time and "-" or "+",
                int_to_string(ticks / (60*60)),
                int_to_string((ticks % (60*60)) / (60)),
                (ticks % 60) / (60) * 10
            )}
        top_table_label.style.horizontally_stretchable = true
    end

    local research_table = table_frame.add{ type = "table", style = "finished_game_table", column_count = 3,}
    research_table.add{ type = "label", caption = "Research", style = "caption_label"}
    research_table.add{ type = "label", caption = "Time", style = "caption_label"}
    research_table.add{ type = "label", caption = "Human", style = "caption_label"}

    local compare_list = human_wr_times[GOAL].research
    for research, time in pairs(global.tas_research) do
        local compare_time = compare_list[research]
        local converted_compare_time
        if compare_time then
            converted_compare_time = compare_time[1] * 60 * 60 *60 + compare_time[2] * 60 * 60 + compare_time[3] * 60
            local ticks = math.abs(time - converted_compare_time)
            compare_time = string.format(
                "%s%s:%s.%d",
                time < converted_compare_time and "-" or "+",
                int_to_string(ticks / (60*60)),
                int_to_string((ticks % (60*60)) / (60)),
                (ticks % 60) / (60) * 10
            )
        end
        
        research_table.add{ type = "label", caption = "[technology="..research.."] "..research..":"}
        research_table.add{ type = "label", style = "bold_label", caption = string.format("%d:%s:%s.%d ",
            time / (60*60*60),
            int_to_string((time % (60*60*60)) / (60*60)),
            int_to_string((time % (60*60)) / (60)),
            (time % 60) / 60 * 10)}
        research_table.add{ type = "label", style = converted_compare_time and time < converted_compare_time and "bold_green_label" or "bold_red_label", caption = compare_time or "N/A"}
    end

    local control_flow = main_frame.add{ type = "flow", direction = "horizontal", style = "dialog_buttons_horizontal_flow"}
    --global.tas_goal_control.finish = control_flow.add{ type="button", style = "red_back_button", caption = "Finish"}
    local w = control_flow.add{ type="empty-widget"}
    w.style.horizontally_stretchable = true
    global.tas_goal_control.continue = control_flow.add{ type="button", style = "confirm_button", caption = "Continue"}
    game.play_sound{path="utility/game_won"}

    main_frame.force_auto_center()
end

script.on_event(defines.events.on_gui_click, function(event)
    if not global.tas_goal_control then return end
    local element = event.element
    if element ==  global.tas_goal_control.continue then
        global.tas_goal_control.main.visible = false
    end
end)

---Display victory gui
---@param message string
local function game_end(message)
    if global.goal and global.goal.completed then return end
    game_end_advanced(message)
    game_end_simple(message)
    --game.set_game_state{game_finished = true, player_won = true, "free-play", can_continue = true}
end

---Event handler for any%
---@param event EventData.on_rocket_launched
local function handle_rocket_launch_event(event)
    if GOAL == anyp then
        game_end(anyp)
        game.reset_game_state()
    end
end

---Event handler for research event that filters steelaxe
---@param event EventData.on_research_finished
local function handle_research_finished_event(event)
    global.tas_research[event.research.name] = game.tick
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
    global.tas_research = global.tas_research or {}
    script.on_event(defines.events.on_research_finished, handle_research_finished_event)
    if GOAL == anyp then
        script.on_event(defines.events.on_rocket_launched, handle_rocket_launch_event)
    elseif GOAL == steelaxe then
        --script.on_event(defines.events.on_research_finished, handle_research_finished_event)
    elseif GOAL ==  gotlap then
        script.on_event(defines.events.script_raised_built, handle_entity_built_event, gotlap_filter)
        script.on_event(defines.events.on_built_entity, handle_entity_built_event, gotlap_filter)
        --script.on_event(defines.events.on_robot_built_entity, gotlap, gotlap_filter) --not needed as robots are not implemented
    elseif GOAL == supply then

    else
        error("Unknown Goal configuration")
    end
end

register_event()
