#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include "Guild3Stuff.h"
#include <iostream>
#include <iostream>
HINSTANCE mHinst = 0, mHinstDLL = 0;
extern "C" UINT_PTR mProcs[53] = {0};
void Console() {
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}


extern "C" void THQNO_AutoInit_wrapper() {

	
		(UINT_PTR)GetProcAddress(mHinstDLL, "THQNO_AutoInit")();

		printf("After : %p", GetProcAddress(mHinstDLL, "THQNO_AutoInit"));
	

}
DWORD WINAPI myThread(LPVOID lpParameter)
{
	//Sleep(5000);

	THQNO_AutoInit_wrapper();
	return 0;
}

LPCSTR mImportNames[] = {"LZ4_compress", "LZ4_compressBound", "LZ4_compress_continue", "LZ4_compress_default", "LZ4_compress_destSize", "LZ4_compress_fast", "LZ4_compress_fast_continue", "LZ4_compress_fast_extState", "LZ4_compress_limitedOutput", "LZ4_compress_limitedOutput_continue", "LZ4_compress_limitedOutput_withState", "LZ4_compress_withState", "LZ4_create", "LZ4_createStream", "LZ4_createStreamDecode", "LZ4_decompress_fast", "LZ4_decompress_fast_continue", "LZ4_decompress_fast_usingDict", "LZ4_decompress_fast_withPrefix64k", "LZ4_decompress_safe", "LZ4_decompress_safe_continue", "LZ4_decompress_safe_partial", "LZ4_decompress_safe_usingDict", "LZ4_decompress_safe_withPrefix64k", "LZ4_freeStream", "LZ4_freeStreamDecode", "LZ4_loadDict", "LZ4_resetStream", "LZ4_resetStreamState", "LZ4_saveDict", "LZ4_setStreamDecode", "LZ4_sizeofState", "LZ4_sizeofStreamState", "LZ4_slideInputBuffer", "LZ4_uncompress", "LZ4_uncompress_unknownOutputSize", "LZ4_versionNumber", "LZ4_versionString", "THQNO_Activity", "THQNO_Apps", "THQNO_AutoInit", "THQNO_Chat", "THQNO_Init", "THQNO_Matchmaking", "THQNO_Networking", "THQNO_Process", "THQNO_RegisterCallback", "THQNO_RestartAppIfNecessary", "THQNO_Shutdown", "THQNO_Stats", "THQNO_UnregisterCallback", "THQNO_User", "THQNO_Utils"};
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if ( fdwReason == DLL_PROCESS_ATTACH ) {
		HINSTANCE hGetProcIDDLL = LoadLibrary("guild3mod.dll");

		if (!hGetProcIDDLL) {
			std::cout << "could not load the dynamic library" << std::endl;
			return EXIT_FAILURE;
		}
		mHinstDLL = LoadLibrary( "ori_thqno_api_x64.dll" );
		if ( !mHinstDLL )
			return ( FALSE );
		for (int i = 0; i < 53; i++) {
			mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
		}
		//Sleep(5000);
		Console();
		HANDLE myHandle = CreateThread(0, 0, myThread, NULL , 0, NULL);
		
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		FreeLibrary( mHinstDLL );
	}
	return ( TRUE );
}

extern "C" void LZ4_compress_wrapper();
extern "C" void LZ4_compressBound_wrapper();
extern "C" void LZ4_compress_continue_wrapper();
extern "C" void LZ4_compress_default_wrapper();
extern "C" void LZ4_compress_destSize_wrapper();
extern "C" void LZ4_compress_fast_wrapper();
extern "C" void LZ4_compress_fast_continue_wrapper();
extern "C" void LZ4_compress_fast_extState_wrapper();
extern "C" void LZ4_compress_limitedOutput_wrapper();
extern "C" void LZ4_compress_limitedOutput_continue_wrapper();
extern "C" void LZ4_compress_limitedOutput_withState_wrapper();
extern "C" void LZ4_compress_withState_wrapper();
extern "C" void LZ4_create_wrapper();
extern "C" void LZ4_createStream_wrapper();
extern "C" void LZ4_createStreamDecode_wrapper();
extern "C" void LZ4_decompress_fast_wrapper();
extern "C" void LZ4_decompress_fast_continue_wrapper();
extern "C" void LZ4_decompress_fast_usingDict_wrapper();
extern "C" void LZ4_decompress_fast_withPrefix64k_wrapper();
extern "C" void LZ4_decompress_safe_wrapper();
extern "C" void LZ4_decompress_safe_continue_wrapper();
extern "C" void LZ4_decompress_safe_partial_wrapper();
extern "C" void LZ4_decompress_safe_usingDict_wrapper();
extern "C" void LZ4_decompress_safe_withPrefix64k_wrapper();
extern "C" void LZ4_freeStream_wrapper();
extern "C" void LZ4_freeStreamDecode_wrapper();
extern "C" void LZ4_loadDict_wrapper();
extern "C" void LZ4_resetStream_wrapper();
extern "C" void LZ4_resetStreamState_wrapper();
extern "C" void LZ4_saveDict_wrapper();
extern "C" void LZ4_setStreamDecode_wrapper();
extern "C" void LZ4_sizeofState_wrapper();
extern "C" void LZ4_sizeofStreamState_wrapper();
extern "C" void LZ4_slideInputBuffer_wrapper();
extern "C" void LZ4_uncompress_wrapper();
extern "C" void LZ4_uncompress_unknownOutputSize_wrapper();
extern "C" void LZ4_versionNumber_wrapper();
extern "C" void LZ4_versionString_wrapper();
extern "C" void THQNO_Activity_wrapper();
extern "C" void THQNO_Apps_wrapper();


extern "C" void THQNO_Chat_wrapper();
extern "C" void THQNO_Init_wrapper();
extern "C" void THQNO_Matchmaking_wrapper();
extern "C" void THQNO_Networking_wrapper();
extern "C" void THQNO_Process_wrapper();
extern "C" void THQNO_RegisterCallback_wrapper();
extern "C" void THQNO_RestartAppIfNecessary_wrapper();
extern "C" void THQNO_Shutdown_wrapper();
extern "C" void THQNO_Stats_wrapper();
extern "C" void THQNO_UnregisterCallback_wrapper();
extern "C" void THQNO_User_wrapper();
extern "C" void THQNO_Utils_wrapper();
