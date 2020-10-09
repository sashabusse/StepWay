#pragma once
#include "../usings.h"
#include "imgui.h"
#include "SignalProcessing/FFT.h"



class MainLayer : public StepWay::Layer
{
public:
	MainLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnGuiUpdate() override;
	virtual void OnEvent(StepWay::Event& e) override;

	virtual std::string ToString() const override;
	virtual std::wstring ToWString() const override;

	virtual ~MainLayer() {};
private:
	void DrawDockSpace();

	void UpdateSignal();
	void UpdateSpectrum();
	void UpdateWavelet();
private:
	ImGuiID m_dock_space_id;
	bool m_continuous_update = false;
	struct MainMenuState
	{
		//Demo
		bool ShowImGuiDemo = false;
		bool ShowImPlotDemo = false;
		//Tools
		bool ShowAppStatistics = false;
		bool ShowStyleEditor = false;
	} m_MainMenuState;

	std::shared_ptr<Texture> m_tex;

	struct SignalData
	{
#define SIGNAL_SIZE (512)
		float noise_amplitude = 1.0;
		float signal_freq = 1.0 / 32;
		std::vector<double> signal = std::vector<double>(SIGNAL_SIZE);
		std::vector<double> time = std::vector<double>(SIGNAL_SIZE);
		std::vector<double> spectrum_abs = std::vector<double>(SIGNAL_SIZE);
		double spectrum_max = 1.0;
		std::vector<double> spectrum_freq = std::vector<double>(SIGNAL_SIZE);
#define MAX_SCALE (40)
		float cwt_result[512 * MAX_SCALE * 3];
	} m_signal_data;
};