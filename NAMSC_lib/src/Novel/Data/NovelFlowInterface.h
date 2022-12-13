#pragma once

/// A Novel element, which is tied to the flow of the Novel and needs to be managed properly
class NovelFlowInterface
{
public:
	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an NovelFlowInterface pointer
	virtual ~NovelFlowInterface() = default;

	/// Checks if the NovelFlowInterface doesn't have any errors, which would halt the Novel execution
	/// \param bComprehensive Checks more error-prone code. This is not desired when loading time is a concern
	virtual bool checkForErrors(bool bComprehensive = false) const = 0;
	
	virtual void run()    = 0;
	virtual void update() = 0;
	virtual void end()    = 0;

	/// Some NovelFlowInterfaces need to access the data, that is a part of the Save
	/// Must be called after the Save is loaded
	virtual void syncWithSave() noexcept = 0;

protected:
	virtual void ensureResourcesAreLoaded() = 0;
};