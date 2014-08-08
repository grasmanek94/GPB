ChangeOPCNIURate(rate) added, changes the update rate of on player closest node id change
Added CreatePolygonAroundPath=true/false parameter in CalculatePath
Added Float:PolygonWidth=10.0 paremeter to CalculatePath which allows you to specify the width arond the path nodes of the polygon, too much or too less and you will destroy the polygon.
Added Float:Polygon[] parameter in path calculated callback.
This is a ready to use polygon for the streamer plugin by incognito.
don't fucking modify the array and complain it doesn't work, nor to me, nor to incognito!

Note that changes made to the node graph won't be visible to the polygon creator until plugin reload (which means you have to restart sa-mp server because it doesn't support such a basic task as "reload library").

No more sampgdk, implemented my own amx native hack.

if you need example scripts, download R181 or older, or look for releases on the sa-mp forum.

From now on you need to manually add AND remove players to/from the OnPlayerClosestNodeIDChange list with "gps_AddPlayer"/"gps_RemovePlayer".