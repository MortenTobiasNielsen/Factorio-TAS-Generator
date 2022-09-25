-- Triggered on research completed
script.on_event(defines.events.on_research_finished, function(event)

	local player = game.players[1]
	if (event.research.name == "steel-axe") then
		local seconds = player.online_time / 60
		local minutes = math.floor(player.online_time / 60 / 60)
		local seconds_remainder = seconds - (minutes * 60)

		player.print(string.format("Congrats %s on reaching the end of your Steel Axe run", player.name), {r=0, g=1, b=0, a=1})
		player.print(string.format("You completed it in %f seconds (%d min %.1f seconds) (%d ticks)", seconds, minutes, seconds_remainder, player.online_time), {r=0, g=1, b=0, a=1})
	
	end

end)

return false