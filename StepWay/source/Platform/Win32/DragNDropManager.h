#pragma once
#include "Log.h"

#include <oleidl.h>


namespace StepWay
{
	namespace Win32
	{

		class DragNDropManager : public IDropTarget
		{
		public:
			//IUncnown interface
			ULONG DragNDropManager::AddRef() override;
			ULONG DragNDropManager::Release() override;
			HRESULT QueryInterface(REFIID riid, void** ppvObject);
		private:
			long m_ref_count = 0;
		public:
			//IDropTarget interface
			// occurs when we drag files into our applications view
			HRESULT DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
			// occurs when we drag files out from our applications view
			HRESULT DragLeave() override;
			// occurs when we drag the mouse over our applications view whilst carrying files (post Enter, pre Leave)
			HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
			// occurs when we release the mouse button to finish the drag-drop operation
			HRESULT Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
		public:
		};

	}
}
