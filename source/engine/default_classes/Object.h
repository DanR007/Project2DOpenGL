#pragma once

class Object
{
public:
	Object();
	virtual ~Object();

	inline bool GetNeedToDestroy() const { return _need_to_destroy; }

	virtual void Destroy() { _need_to_destroy = true; }
protected:
	void SetNeedToDestroy() { _need_to_destroy = true; }

	bool _need_to_destroy;
};