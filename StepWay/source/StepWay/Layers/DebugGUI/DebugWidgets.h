#pragma once
#include "Core.h"
#include "imgui.h"
#include "glm/glm.hpp"


namespace StepWay
{

	enum class DbgWidgetType : int
	{
		NONE = 0,
		BUTTON,
		SLIDER_FLOAT,
		SLIDER_FLOAT2,
		SLIDER_FLOAT3,
		SLIDER_FLOAT4,
		SLIDER_INT,
		SLIDER_INT2,
		SLIDER_INT3,
		SLIDER_INT4,
		INPUT_INT,
		INPUT_INT2,
		INPUT_INT3,
		INPUT_INT4,
		INPUT_FLOAT,
		INPUT_FLOAT2,
		INPUT_FLOAT3,
		INPUT_FLOAT4,
		CHECK_BOX,
		COLOR_FLOAT4
	};

#define SW_DECLARE_DBG_WIDGET_TYPE(type)\
		static DbgWidgetType GetStaticWidgetType(){return type;}\
		virtual DbgWidgetType GetWidgetType() const override { return GetStaticWidgetType(); }\


	class DbgWidget
	{
	public:
		virtual DbgWidgetType GetWidgetType()const = 0;

		virtual void Show() = 0;

		virtual ~DbgWidget() {};
	private:
	public:
	private:
	};

	template<typename ItemType>
	class DbgSliderBase : public DbgWidget
	{
	public:
		virtual ~DbgSliderBase() {};
	protected:
		DbgSliderBase(const std::string& name, ItemType* pvalue, ItemType min, ItemType max, const std::string& format) :
			m_name(name), m_pvalue(pvalue), m_min(min), m_max(max), m_format(format) {};

		std::string m_name;
		ItemType* m_pvalue;
		ItemType m_min, m_max;
		std::string m_format;
	};



	//FLOATS-----------------------------------------------
	class DbgSliderf : public DbgSliderBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_FLOAT);
		DbgSliderf(const std::string& name, float* pvalue, float min, float max, const std::string& format = "%.3f") :
			DbgSliderBase<float>(name, pvalue, min, max, format) {};
		virtual ~DbgSliderf() {};

		void Show() override;
	};
	

	class DbgSlider2f : public DbgSliderBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_FLOAT2);
		DbgSlider2f(const std::string& name, float* pvalue, float min, float max, const std::string& format = "%.3f") :
			DbgSliderBase<float>(name, pvalue, min, max, format) {};
		virtual ~DbgSlider2f() {};
	
		void Show() override;
	};
	

	class DbgSlider3f : public DbgSliderBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_FLOAT3);
		DbgSlider3f(const std::string& name, float* pvalue, float min, float max, const std::string& format = "%.3f") :
			DbgSliderBase<float>(name, pvalue, min, max, format) {};
		virtual ~DbgSlider3f() {};

		void Show() override;
	};


	class DbgSlider4f : public DbgSliderBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_FLOAT4);
		DbgSlider4f(const std::string& name, float* pvalue, float min, float max, const std::string& format = "%.3f") :
			DbgSliderBase<float>(name, pvalue, min, max, format) {};
		virtual ~DbgSlider4f() {};

		void Show() override;
	};



	//INTEGER------------------------------------------
	class DbgSlideri : public DbgSliderBase<int>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_INT);
		DbgSlideri(const std::string& name, int* pvalue, int min, int max, const std::string& format = "%d") :
			DbgSliderBase<int>(name, pvalue, min, max, format) {};
		virtual ~DbgSlideri() {};
	
		void Show() override;
	};
	
	
	class DbgSlider2i : public DbgSliderBase<int>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_INT2);
		DbgSlider2i(const std::string& name, int* pvalue, int min, int max, const std::string& format = "%d") :
			DbgSliderBase<int>(name, pvalue, min, max, format) {};
		virtual ~DbgSlider2i() {};
	
		void Show() override;
	};
	

	class DbgSlider3i : public DbgSliderBase<int>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_INT3);
		DbgSlider3i(const std::string& name, int* pvalue, int min, int max, const std::string& format = "%d") :
			DbgSliderBase<int>(name, pvalue, min, max, format) {};
		virtual ~DbgSlider3i() {};
	
		void Show() override;
	};
	

	class DbgSlider4i : public DbgSliderBase<int>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::SLIDER_INT4);
		DbgSlider4i(const std::string& name, int* pvalue, int min, int max, const std::string& format = "%d") :
			DbgSliderBase<int>(name, pvalue, min, max, format) {};
		virtual ~DbgSlider4i() {};
	
		void Show() override;
	};



	//Checkbox
	class DbgCheckBox : public DbgWidget
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::CHECK_BOX);
		DbgCheckBox(const std::string& name, bool* pval) :
			m_name(name), m_pval(pval) {};
		virtual ~DbgCheckBox() {};

		virtual void Show() override;
	private:
		std::string m_name;
		bool* m_pval;
	};

	

	template<typename ItemType>
	class DbgInputBase : public DbgWidget
	{
	public:
		DbgInputBase(const std::string& name, ItemType* pval) :
			m_name(name), m_pval(pval) {};
		virtual ~DbgInputBase() {};

	protected:
		std::string m_name;
		ItemType* m_pval;
	};


	class DbgInputf : public DbgInputBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::INPUT_FLOAT);
		DbgInputf(const std::string& name, float* pval) :
			DbgInputBase<float>(name, pval) {};
		virtual ~DbgInputf() {};

		virtual void Show() override;
	};

	class DbgInput2f : public DbgInputBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::INPUT_FLOAT);
		DbgInput2f(const std::string& name, float* pval) :
			DbgInputBase<float>(name, pval) {};
		virtual ~DbgInput2f() {};

		virtual void Show() override;
	};

	class DbgInput3f : public DbgInputBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::INPUT_FLOAT);
		DbgInput3f(const std::string& name, float* pval) :
			DbgInputBase<float>(name, pval) {};
		virtual ~DbgInput3f() {};

		virtual void Show() override;
	};

	class DbgInput4f : public DbgInputBase<float>
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::INPUT_FLOAT);
		DbgInput4f(const std::string& name, float* pval) :
			DbgInputBase<float>(name, pval) {};
		virtual ~DbgInput4f() {};

		virtual void Show() override;
	};


	class DbgColor4f : public DbgWidget
	{
	public:
		SW_DECLARE_DBG_WIDGET_TYPE(DbgWidgetType::COLOR_FLOAT4);
		DbgColor4f(const std::string& name, float* pval) :
			m_name(name), m_pval(pval) {};

		virtual void Show() override;

		virtual ~DbgColor4f() {};
	private:

	public:
	private:
		std::string m_name;
		float* m_pval;
	};

}