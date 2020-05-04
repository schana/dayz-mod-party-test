modded class SchanaPartyManagerServer {
	static const int MOCK_PLAYER_COUNT = 100;

	override private ref map<ref string, ref vector> GetPositions () {
		auto positions = super.GetPositions ();

		for (int i = 0; i < MOCK_PLAYER_COUNT; ++i) {
			positions.Insert (i.ToString (), "0 0 0");
		}

		return positions;
	}

	override private ref map<ref string, ref float> GetHealths () {
		auto healths = super.GetHealths ();

		for (int i = 0; i < MOCK_PLAYER_COUNT; ++i) {
			healths.Insert (i.ToString (), 100);
		}

		return healths;
	}

	override private void SendPlayersInfo (ref map<ref string, ref PlayerBase> id_map) {
		auto all_player_ids = new ref array<ref string>;
		auto all_player_names = new ref array<ref string>;
		foreach (auto player_id, auto player_base_player : id_map) {
			all_player_ids.Insert (player_id);
			all_player_names.Insert (player_base_player.GetIdentity ().GetName ());
		}
		for (int i = 0; i < MOCK_PLAYER_COUNT; ++i) {
			all_player_ids.Insert (i.ToString ());
			all_player_names.Insert ("Name " + i.ToString ());
		}

		auto all_player_info = new ref Param2<ref array<ref string>, ref array<ref string>> (all_player_ids, all_player_names);

		if (SchanaPartyUtils.WillLog (SchanaPartyUtils.DEBUG)) {
			string result;
			JsonSerializer ().WriteToString (all_player_info, false, result);
			SchanaPartyUtils.Debug ("SendPlayers " + result);
		}

		GetRPCManager ().SendRPC ("SchanaModParty", "ClientUpdatePlayersInfoRPC", all_player_info);
	}
}