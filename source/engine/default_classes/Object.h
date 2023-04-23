#pragma once

class Object
{
public:
	Object();
	~Object();

	void SetNeedToDestroy() { _need_to_destroy = true; }

	inline bool GetNeedToDestroy() const { return _need_to_destroy; }

	virtual void Destroy() { _need_to_destroy = true; }
protected:

	bool _need_to_destroy;
};