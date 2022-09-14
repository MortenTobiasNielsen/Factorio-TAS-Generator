-- Triggered on item built
script.on_event(defines.events.script_raised_built , function(event)

	if (event.entity.name == "locomotive") then
		local seconds = player.online_time / 60
		local minutes = math.floor(player.online_time / 60 / 60)
		local seconds_remainder = seconds - (minutes * 60)

		player.print(string.format("Congrats %s on reaching the end of your Getting On Track Like A Pro run", player.name), {r=0, g=1, b=0, a=1})
		player.print(string.format("You completed it in %f seconds (%d min %.1f seconds) (%d ticks)", seconds, minutes, seconds_remainder, player.online_time), {r=0, g=1, b=0, a=1})

		debug_state = false
	end

end)