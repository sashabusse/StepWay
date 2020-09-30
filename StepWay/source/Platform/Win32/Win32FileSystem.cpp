#include "StepWayPCH.h"
#include "Win32FileSystem.h"
#include "Utility.h"

#include <windows.h>
#include <shobjidl.h>

namespace StepWay
{
	namespace Win32
	{
        std::vector<std::string> Win32FileSystem::FileChooseDialog()
        {
            std::vector<std::string> filenames;
            HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                COINIT_DISABLE_OLE1DDE);
            if (SUCCEEDED(hr))
            {
                IFileOpenDialog* pFileOpen;

                // Create the FileOpenDialog object.
                hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                    IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

                if (SUCCEEDED(hr))
                {
                    // Show the Open dialog box.
                    hr = pFileOpen->Show(NULL);

                    // Get the file name from the dialog box.
                    if (SUCCEEDED(hr))
                    {
                        IShellItem* pItem;
                        hr = pFileOpen->GetResult(&pItem);
                        if (SUCCEEDED(hr))
                        {
                            PWSTR pszFilePath;
                            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                            // Display the file name to the user.
                            if (SUCCEEDED(hr))
                            {
                                filenames.push_back(Utility::Utf16ToUtf8(pszFilePath));
                                CoTaskMemFree(pszFilePath);
                            }
                            pItem->Release();
                        }
                    }
                    pFileOpen->Release();
                }
                CoUninitialize();
            }
            return std::move(filenames);
        }

        std::string Win32FileSystem::GetWorkingDirectory()
        {
            const DWORD buf_len = 512;
            WCHAR cur_dir[buf_len] = { 0 };
            DWORD result = GetCurrentDirectory(buf_len, cur_dir);
            SW_CORE_ASSERT(result != 0, "failed get current directory");

            return Utility::Utf16ToUtf8(cur_dir);
        }

	}
}
