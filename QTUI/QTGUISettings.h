#pragma once

#include <string>

class QTGUISettings
{
public:
	static QTGUISettings& GetInstance();
	void Load(std::string fileName);
	void Save(std::string fileName);

	// Setters and Getters
	int GetMonitorIndex();
	void SetMonitorIndex(int nMonitorIndex);

private:
	int m_MonitorIndex;
};
