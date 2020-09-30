#include "StepWayPCH.h"
#include "DragNDropManager.h"
#include "Application.h"
#include "Events/DragNDropEvents.h"
#include "Win32Window.h"

#include <shellapi.h>

namespace StepWay
{
	namespace Win32
	{
		ULONG DragNDropManager::AddRef()
		{
			return InterlockedIncrement(&m_ref_count);
		}
		ULONG DragNDropManager::Release()
		{
			long nRefCount = 0;
			nRefCount = InterlockedDecrement(&m_ref_count);
			if (nRefCount == 0) delete this;
			return nRefCount;
		}

		HRESULT DragNDropManager::QueryInterface(REFIID riid, void** ppvObject)
		{
			if (riid == IID_IUnknown)
			{
				*ppvObject = static_cast<IUnknown*>(this);
				AddRef();

				return S_OK;
			}
			if (riid == IID_IDropTarget)
			{
				*ppvObject = static_cast<IUnknown*>(this);
				AddRef();

				return S_OK;
			}

			*ppvObject = NULL;
			return E_NOINTERFACE;
		}



		HRESULT DragNDropManager::DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
		{

			// TODO: check whether we can handle this type of object at all and set *pdwEffect &= DROPEFFECT_NONE if not;
			Application::GetInstance().OnEvent(DragEnterEvent());
			return S_OK;
		}

		HRESULT DragNDropManager::DragLeave()
		{
			SW_INFO("Drag Leave"); 
			Application::GetInstance().OnEvent(DragLeaveEvent());
			return S_OK;
		}

		HRESULT DragNDropManager::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
		{
			POINT pos = {pt.x, pt.y};
			ScreenToClient(((Win32::Win32Window&)Application::GetWindow()).GetHWND(), &pos);
			Application::GetInstance().OnEvent(DragOverEvent(pos.x, pos.y));
			*pdwEffect &= DROPEFFECT_COPY;
			return S_OK;
		}


		HRESULT DragNDropManager::Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
		{
			// render the data into stgm using the data description in fmte
			FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
			STGMEDIUM stgm;


			if (SUCCEEDED(pDataObj->GetData(&fmte, &stgm)))
			{
				HDROP hdrop = reinterpret_cast<HDROP>(stgm.hGlobal);

				std::vector<std::wstring> filenames;

				UINT file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
				for (UINT i = 0; i < file_count; i++)
				{
					TCHAR szFile[MAX_PATH];
					UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);
					if (cch > 0 && cch < MAX_PATH)
					{
						filenames.push_back(szFile);
					}
				}

				ReleaseStgMedium(&stgm);
				
				if (!filenames.empty())
				{
					Application::GetInstance().OnEvent(DropEvent(std::move(filenames)));
					*pdwEffect &= DROPEFFECT_COPY;
				}
				else
				{
					*pdwEffect &= DROPEFFECT_NONE;
				}
			}

			return S_OK;
		}


	}
}