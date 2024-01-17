#pragma once

#include "Sample.h"

DEF_SAMPLE(DF)
{
  const std::tstring FILE_DIR  = ts("C:\\Intel\\Logs\\");
  const std::tstring FILE_PATH = ts("C:\\Intel\\Logs\\IntelGFX.log");

  std::tcout << (vu::is_directory_exists(FILE_DIR) ? ts("Directory is exist") : ts("Directory isn't exist")) << std::endl;
  std::tcout << (vu::is_file_exists(FILE_PATH) ? ts("File is exist") : ts("File isn't exist")) << std::endl;

  std::tcout << vu::get_file_type(FILE_PATH) << std::endl;

  std::tcout << vu::extract_file_directory(FILE_PATH) << std::endl;
  std::tcout << vu::extract_file_directory(FILE_PATH, false) << std::endl;

  std::tcout << vu::extract_file_name(FILE_PATH) << std::endl;
  std::tcout << vu::extract_file_name(FILE_PATH, false) << std::endl;

  std::tcout << vu::get_current_directory() << std::endl;
  std::tcout << vu::get_current_directory(false) << std::endl;

  std::tcout << vu::get_contain_directory() << std::endl;
  std::tcout << vu::get_contain_directory(false) << std::endl;

  std::tcout << vu::get_current_file_path() << std::endl;

  std::tcout << vu::join_path(ts("C:\\path\\to\\"), ts("\\file.exe")) << std::endl;
  std::tcout << vu::join_path(ts("C:\\path\\to\\"), ts("file.exe")) << std::endl;
  std::tcout << vu::join_path(ts("C:\\path\\to"), ts("\\file.exe")) << std::endl;
  std::tcout << vu::join_path(ts("C:\\path\\to"), ts("file.exe")) << std::endl;

  std::tcout << vu::normalize_path(ts("C:/path/to/file.exe"), vu::path_separator::POSIX) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\path\\to\\file.exe"), vu::path_separator::POSIX) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\path\\\\to\\file.exe"), vu::path_separator::POSIX) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\path\\\\to\\file.exe"), vu::path_separator::POSIX) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\\\path\\to/file.exe"), vu::path_separator::POSIX) << std::endl;

  std::tcout << vu::normalize_path(ts("C:/path/to/file.exe")) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\path\\to\\file.exe")) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\path\\\\to\\file.exe")) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\path\\\\to\\file.exe")) << std::endl;
  std::tcout << vu::normalize_path(ts("C:\\\\path\\to/file.exe")) << std::endl;

  vu::Path file_dir;
  file_dir.join(ts("   C:/Users")).join(ts("/Vic")).join(ts("\\.vscode\\")).finalize();

  vu::Path file_dir_tmp = std::tstring(ts("C:/Users/Vic\\.vscode\\extensions"));
  
  vu::Path file_path(file_dir);
  file_path += vu::Path(ts("argv.json"));
  file_path.finalize();

  vu::Path file_path_tmp(file_dir);
  file_path_tmp = file_path_tmp + vu::Path(ts("argv-tmp.json"));
  file_path_tmp.finalize();

  std::tcout << file_dir  << std::endl;
  std::tcout << file_dir_tmp << std::endl;

  std::tcout << file_path << std::endl;
  std::tcout << file_path_tmp << std::endl;

  std::tcout << (file_path == file_path_tmp) << std::endl;
  std::tcout << (file_path != file_path_tmp) << std::endl;

  std::tcout << ts("Exists (Dir)  : ") << file_dir.exists() << std::endl;
  std::tcout << ts("Exists (File) : ") << file_path.exists() << std::endl;

  std::tcout << ts("File Name : ") << file_path.extract_name().as_string() << std::endl;
  std::tcout << ts("File Directory : ") << file_path.extract_directory().as_string() << std::endl;

  auto path = ts("C:\\");
  std::tcout << vu::check_path_permissions(path, GENERIC_READ) << std::endl;
  std::tcout << vu::check_path_permissions(path, GENERIC_READ | GENERIC_WRITE) << std::endl;
  std::tcout << vu::check_path_permissions(path, GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE) << std::endl;

  // TODO: Vic. Uncompleted.

  #ifdef _WIN64
  #define EXE_NAME ts("x64dbg.exe")
  #else  // _WIN32
  #define EXE_NAME ts("x32dbg.exe")
  #endif // _WIN64
  
  auto PIDs = vu::name_to_pid(EXE_NAME);
  if (!PIDs.empty())
  {
    vu::ulong PID = *PIDs.begin();

    std::cout << std::hex << vu::remote_get_module_handle_A(PID, "kernel32.dll") << std::endl;
    std::tcout << vu::get_last_error() << std::endl;

    std::wcout << std::hex << vu::remote_get_module_handle_W(PID, L"kernel32.dll") << std::endl;
    std::tcout << vu::get_last_error() << std::endl;
  }

  return vu::VU_OK;
}
