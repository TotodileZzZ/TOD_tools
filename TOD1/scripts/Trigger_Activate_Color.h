class Trigger_Activate_Color : public Scriptbaked
{
public:
	static Scriptbaked* Create()
	{
		static Scriptbaked* inst = new Scriptbaked("Trigger_Activate_Color", "Node", false, false);
		
		//	TODO: add members and methods to Trigger_Activate_Color.
		
		inst->CalculateSize();
		
		return inst;
	};
};

Trigger_Activate_Color::Create();