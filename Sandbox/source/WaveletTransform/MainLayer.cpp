#include "MainLayer.h"
#include <memory>
#include "imgui.h"
#include "implot.h"
#include "SignalProcessing/SPUtil.h"
#include "SignalProcessing/FFT.h"
#include "SignalProcessing/WT.h"
#include <algorithm>




MainLayer::MainLayer()
{
}

void MainLayer::OnAttach()
{
	m_tex = std::shared_ptr<Texture>(Texture::Create(GAPI_TYPE::OPENGL));
	m_tex->SetUp(512, MAX_SCALE, Texture::PixelFormat::RGB32_F, NULL);
	Application::GetWindow().Maximize();
	UpdateSignal();
	UpdateSpectrum();
	UpdateWavelet();
}

void MainLayer::OnDetach()
{
	m_tex->ShutDown();
}

void MainLayer::OnUpdate()
{
	RenderingCommands::Clear();
}

void MainLayer::OnGuiUpdate()
{
	static bool dock_space = true;
	DrawDockSpace();
	//Demos
	if (m_MainMenuState.ShowImGuiDemo) { ImGui::ShowDemoWindow(&m_MainMenuState.ShowImGuiDemo); }
	if (m_MainMenuState.ShowImPlotDemo) { ImPlot::ShowDemoWindow(&m_MainMenuState.ShowImPlotDemo); }
	//Tools
	if (m_MainMenuState.ShowAppStatistics) { ImGui::ShowMetricsWindow(&(m_MainMenuState.ShowAppStatistics)); }
	if (m_MainMenuState.ShowStyleEditor) { ImGui::Begin("Style Editor", &(m_MainMenuState.ShowStyleEditor)); ImGui::ShowStyleEditor(); ImGui::End(); }
	

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Tool"))
		{
			ImGui::MenuItem("Metrics", NULL, &(m_MainMenuState.ShowAppStatistics));
			ImGui::MenuItem("Style Editor", NULL, &(m_MainMenuState.ShowStyleEditor));
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Demo"))
		{
			ImGui::MenuItem("ImGui", NULL, &(m_MainMenuState.ShowImGuiDemo));
			ImGui::MenuItem("ImPlot", NULL, &(m_MainMenuState.ShowImPlotDemo));
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	
	ImGui::Begin("Param Control");
	ImGui::DragFloat("Amplitude", &m_signal_data.noise_amplitude, 0.01, 0.0001);
	ImGui::DragFloat("Frequency", &m_signal_data.signal_freq, 0.01, 0.0001);

	if (ImGui::Button("Generate") || m_continuous_update)
	{
		UpdateSignal();
		UpdateSpectrum();
		UpdateWavelet();
	}
	ImGui::Checkbox("Continuous Update", &m_continuous_update);
	ImGui::End();

	ImGui::Begin("Signal");
	
	ImPlot::SetNextPlotLimitsY(-2, 2, ImGuiCond_FirstUseEver);
	ImPlot::SetNextPlotLimitsX(m_signal_data.time[0], m_signal_data.time.back(), ImGuiCond_FirstUseEver);
	auto sz = ImGui::GetWindowContentRegionMax();
	sz.y -= 15;
	if (ImPlot::BeginPlot("##Signal", NULL, NULL, sz, NULL, NULL)) {
		ImPlot::PlotLine("Signal", &m_signal_data.time[0], &m_signal_data.signal[0], m_signal_data.signal.size());
		ImPlot::EndPlot();
	}

	ImGui::End();

	ImGui::Begin("Spectrum");

	ImPlot::SetNextPlotLimitsY(0.0, m_signal_data.spectrum_max, ImGuiCond_FirstUseEver);
	ImPlot::SetNextPlotLimitsX(m_signal_data.spectrum_freq[0], m_signal_data.spectrum_freq.back(), ImGuiCond_FirstUseEver);
	if (ImPlot::BeginPlot("##Spectrum", NULL, NULL, ImGui::GetWindowContentRegionMax(), NULL, NULL)) {
		ImPlot::PlotLine("Spectrum", &m_signal_data.spectrum_freq[0], &m_signal_data.spectrum_abs[0], m_signal_data.spectrum_abs.size());
		ImPlot::EndPlot();
	}

	ImGui::End();

	ImGui::Begin("Wavelet");

	static ImVec2 bmin(0, 0);
	static ImVec2 bmax(1, 1);
	static ImVec2 uv0(0, 0);
	static ImVec2 uv1(1, 1);
	static ImVec4 tint(1, 1, 1, 1);

	ImPlot::SetNextPlotLimitsY(0, 1, ImGuiCond_Always);
	ImPlot::SetNextPlotLimitsX(0, 1, ImGuiCond_Always);
	if (ImPlot::BeginPlot("##CWT_RESULT", NULL, NULL, ImGui::GetWindowContentRegionMax(), NULL, NULL)) {
		ImPlot::PlotImage("CWT_RESULT", (ImTextureID)m_tex->GetNativeTexture(), bmin, bmax, uv0, uv1, tint);
		ImPlot::EndPlot();
	}

	ImGui::End();

}


void MainLayer::UpdateSignal()
{
	for (int i = 0; i < m_signal_data.signal.size(); i++)
	{
		m_signal_data.time[i] = i;
		m_signal_data.signal[i] = sin(2 * M_PI * m_signal_data.signal_freq * i) + (((double)rand() / RAND_MAX) * 2 - 1) * m_signal_data.noise_amplitude;
	}
}

void MainLayer::UpdateSpectrum()
{
	std::vector<FFT::cmplx> fft_result = FFT::fft(m_signal_data.signal);
	for (int i = 0; i < fft_result.size(); i++)
	{
		m_signal_data.spectrum_abs[i] = abs(fft_result[i]);
		m_signal_data.spectrum_max = std::max(m_signal_data.spectrum_max, abs(fft_result[i]));
	}

	FFT::make_symmetrical_inplace(m_signal_data.spectrum_abs);
	m_signal_data.spectrum_freq = FFT::symmetrical_freqs(m_signal_data.signal.size(), 1.0);
}
void MainLayer::UpdateWavelet()
{
	WT::MexHWavelet wv;

	for (int i = 0; i < MAX_SCALE; i++)
	{
		std::vector<double> result = WT::cwt(m_signal_data.signal, wv, i + 1);
		for (int j = 0; j < result.size(); j++)
		{
			m_signal_data.cwt_result[3 * (j + i * 512)] = 0;
			m_signal_data.cwt_result[3 * (j + i * 512) + 1] = 0;
			m_signal_data.cwt_result[3 * (j + i * 512) + 2] = 0;
			double tmp = result[j] / 4;
			double b = (1 - tmp) / 2;
			double r = (tmp + 1) / 2;
			if (b > 0)
				m_signal_data.cwt_result[3 * (j + i * 512) + 2] = b;
			if (r > 0)
				m_signal_data.cwt_result[3 * (j + i * 512)] = r;
		}
	}

	m_tex->LoadData(512, MAX_SCALE, Texture::PixelFormat::RGB32_F, m_signal_data.cwt_result);
}

void MainLayer::OnEvent(StepWay::Event& e)
{
}

std::string MainLayer::ToString() const
{
	return std::string("Wavelet Transform Main Layer");
}

std::wstring MainLayer::ToWString() const
{
	return std::wstring(L"Wavelet Transform Main Layer");
}
