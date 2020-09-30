#pragma once
#include "Event.h"
#include "Input/InputDefs.h"
#include "Utility.h"


namespace StepWay
{

	class DragNDropEvent : public Event
	{
	public:
		SW_DECLARE_EVENT_CATEGORY(DRAGNDROP_CATEGORY);


		virtual std::string ToString() const
		{
			return GetTypeString();
		};
		virtual std::wstring ToWString() const
		{
			return GetTypeWString();
		};

	protected:
		DragNDropEvent() {};

	};


	class DragEnterEvent : public DragNDropEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::DRAGNDROP_ENTER);


		DragEnterEvent() :
			DragNDropEvent()
		{};

		~DragEnterEvent() override {};
	private:
	};


	class DragLeaveEvent : public DragNDropEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::DRAGNDROP_LEAVE);


		DragLeaveEvent() :
			DragNDropEvent()
		{};

		~DragLeaveEvent() override {};
	private:
	};


	class DragOverEvent : public DragNDropEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::DRAGNDROP_OVER);


		DragOverEvent(float x, float y) :
			DragNDropEvent(),
			m_x(x),
			m_y(y)
		{};

		float GetX() { return m_x; };
		float GetY() { return m_y; };

		~DragOverEvent() override {};
	private:
		float m_x;
		float m_y;
	};


	class DropEvent : public DragNDropEvent
	{
	public:
		SW_DECLARE_EVENT_TYPE(EventType::DRAGNDROP_DROP)

		//copy constructor
		DropEvent(const std::vector<std::wstring>& filenames):
			DragNDropEvent(),
			m_filenames(filenames)
		{};
		//move constructor
		DropEvent(std::vector<std::wstring>&& filenames) :
			DragNDropEvent(),
			m_filenames(std::move(filenames))
		{};

		std::vector<std::wstring>& GetFilenames() { return m_filenames; };
		int GetSize() { return m_filenames.size(); };
		std::string GetFilename(int i) { return Utility::Utf16ToUtf8(m_filenames[i]); }
		const std::wstring& GetWFilename(int i) { return m_filenames[i]; };

		~DropEvent() override {};
	private:
		std::vector<std::wstring> m_filenames;
	};


}