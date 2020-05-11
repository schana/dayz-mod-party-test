modded class SchanaPartyMarkerManagerServer {

    override private void SendMarkerInfoToPlayer (string id, ref set<ref string> party_ids, PlayerBase player) {
        auto playerMarkers = new ref array<ref SchanaPartyMarkerInfo>;
        foreach (string party_id : party_ids) {
            foreach (auto m : markers.Get (party_id)) {
                playerMarkers.Insert (m);
            }
        }

        playerMarkers.Insert(new SchanaPartyMarkerInfo("test a", "100 100 100"));
        playerMarkers.Insert(new SchanaPartyMarkerInfo("test b", "200 200 200"));
        playerMarkers.Insert(new SchanaPartyMarkerInfo("test c", "300 300 300"));

        auto info = new ref Param1<ref array<ref SchanaPartyMarkerInfo>> (playerMarkers);

        if (SchanaPartyUtils.WillLog (SchanaPartyUtils.DEBUG)) {
            string result;
            JsonSerializer ().WriteToString (info, false, result);
            SchanaPartyUtils.Debug ("SendMarkers to " + id + " " + result);
        }

        if (player && player.GetIdentity ()) {
            GetRPCManager ().SendRPC ("SchanaModPartyPluginVPPMap", "ClientUpdatePartyMarkersRPC", info, false, player.GetIdentity ());
        } else {
            SchanaPartyUtils.Warn ("SendMarkers failed to " + id);
        }
    }
}