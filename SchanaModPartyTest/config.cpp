class CfgPatches
{
	class SchanaModPartyTest
	{
		requiredAddons[] = {};
		units[] = {};
		weapons[] = {};
	};
};

class CfgMods
{
	class SchanaModPartyTest
	{
		name = "SchanaModPartyTest";
		action = "https://github.com/schana/dayz-mod-party-test";
		author = "schana";
		type = "mod";
		dependencies[] =
		{
			"Mission"
		};
		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {
					"SchanaModPartyTest/Mission"
				};
			};
		};
	};
};
