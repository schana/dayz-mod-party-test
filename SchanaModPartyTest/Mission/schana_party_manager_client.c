modded class SchanaPartyManagerClient {
    void SchanaPartyManagerClient () {
        SchanaPartyUtils.LogMessage ("Test Client Init " + MissionBase.SCHANA_PARTY_VERSION);

        //GetGame ().GetCallQueue (CALL_CATEGORY_GUI).CallLater (this.MockUpdate, 5000, true);
        //GetGame ().GetCallQueue (CALL_CATEGORY_GUI).CallLater (this.TestConfigLoading, 200, true);
    }

    void ~SchanaPartyManagerClient () {
        GetGame ().GetCallQueue (CALL_CATEGORY_GUI).Remove (this.MockUpdate);
        GetGame ().GetCallQueue (CALL_CATEGORY_GUI).Remove (this.TestConfigLoading);
    }

    void MockUpdate () {
        for (int i = 0; i < SchanaPartyManagerServer.MOCK_PLAYER_COUNT; ++i) {
            auto members = new ref array<ref string>;
            int j = i % 10;
            while (j < SchanaPartyManagerServer.MOCK_PLAYER_COUNT) {
                members.Insert (j.ToString ());
                j = j + 10;
            }
            auto data = new Param2<ref string, ref array<ref string>> (i.ToString (), members);
            GetRPCManager ().SendRPC ("SchanaModParty", "ServerRegisterPartyRPC", data);
        }
    }

    int test_config_counter = 0;

    void TestConfigLoading () {
        auto test_settings = SchanaModPartySettings.Get ();
        if (test_config_counter > 0 && !test_settings.Contains ((test_config_counter - 1).ToString ())) {
            Print("[SchanaParty] Test Error loading configuration");
        }
        test_settings.Add (test_config_counter.ToString (), "name " + test_config_counter.ToString ());
        test_config_counter++;
    }
}