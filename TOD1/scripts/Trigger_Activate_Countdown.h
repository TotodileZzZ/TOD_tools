class Trigger_Activate_Countdown : public Scriptbaked
{
public:
	static Scriptbaked* Create()
	{
		static Scriptbaked* inst = new Scriptbaked("Trigger_Activate_Countdown", "Node", false, false);
		
		//	TODO: add members and methods to Trigger_Activate_Countdown.
		
		inst->CalculateSize();
		
		return inst;
	};
};

Trigger_Activate_Countdown::Create();