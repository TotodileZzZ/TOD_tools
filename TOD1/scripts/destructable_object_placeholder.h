class destructable_object_placeholder : public Scriptbaked
{
public:
	static Scriptbaked* Create()
	{
		static Scriptbaked* inst = new Scriptbaked("destructable_object_placeholder", "Node", false, false);
		
		//	TODO: add members and methods to destructable_object_placeholder.
		
		inst->CalculateSize();
		
		return inst;
	};
};

destructable_object_placeholder::Create();