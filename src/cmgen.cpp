#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

int main(int argc, char *argv[]) {

  char language = 'c';
  bool PJL = false;
  bool force = false;
  bool PJV = false;
  char *ProjectVersion;
  bool PJI = false;
  const char *ProjectName;
  bool PJN = false;

  std::cout << " #####  #       # #####  ##### #     #" << std::endl;
  std::cout << "#     # ##     ## #      #     ##    #" << std::endl;
  std::cout << "#       # #   # # #  ##  ###   #  #  #" << std::endl;
  std::cout << "#     # #  # #  # #   ## #     #    ##" << std::endl;
  std::cout << " #####  #   #   #  ### # ##### #     #" << std::endl;
  std::cout << "Written by : CSQ" << std::endl;

  //===========================================================================
  // Program Init
  //===========================================================================
  for (int i = 1; i < argc; i++) {

    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'h':
        std::cout
            << "cmgen [-l c/j (c/c++/java) ] [-n] ProjectName [-v "
               "Project version] [-f] [-i]"
            << std::endl
            << "cmgen : " << std::endl
            << "\t-h This sheet!"
            << "\t-l Programing Language : c / j" << std ::endl
            << "\t-n Project Name" << std ::endl
            << "\t-v Project Version" << std ::endl
            << "\t-i Generate basic install setting" << std ::endl
            << "\t-f Force Mode (Gen Project when \"CMakeLists.txt\" existed)"
            << std::endl;
        exit(0);
        break;

        // Language Select
        //-------------------------------------------
      case 'l':
      case 'L':
        PJL = true;
        if (argv[i][2] == '\0') {
          i++;
          if (i < argc && (argv[i][0] == 'c' || argv[i][0] == 'C')) {
            language = 'c';
          } else if (i < argc && (argv[i][0] == 'j' || argv[i][0] == 'J')) {
            language = 'j';
          } else {
            std::cout << "[ERROR] Only support C/C++ and Java Language!"
                      << std::endl;
          }
        } else {
          if (argv[i][2] == 'c' || argv[i][2] == 'C') {
            language = 'c';
          } else if (argv[i][2] == 'j' || argv[i][2] == 'J') {
            language = 'j';
          } else {
            std::cout << "[ERROR] Only support C/C++ and Java Language!"
                      << std::endl;
          }
        }
        break;
        // Project name
        //-------------------------------------------
      case 'n':
        PJN = true;
        if (argv[i][2] == '\0') {
          i++;
          if (i < argc)
            ProjectName = argv[i];
        } else {
          ProjectName = (argv[i] + 2);
        }
        std::cout << "[INFO] Project name:" << ProjectName << std::endl;
        break;

        // Force mode
        //--------------------------------------------
      case 'f':
      case 'F':
        force = true;
        break;

        // Project Name
        //--------------------------------------------
      case 'v':
        PJV = true;

        if (argv[i][2] == '\0') {
          i++;
          if (i < argc)
            ProjectVersion = argv[i];
        } else {
          ProjectVersion = (argv[i] + 2);
        }

        break;

        // Install
        //--------------------------------------------
      case 'i':
      case 'I':
        PJI = true;
        break;
      }
    } else {
      ProjectName = argv[i];
      PJN = true;
    }
  }

  //============================================================================
  // Main
  //============================================================================

  // CMakeLists.txt
  //--------------------
  if (!force) {
    std::fstream isExist;
    isExist.open("./CMakeLists.txt");
    if (isExist.is_open()) {
      std::cout << "[ERROR] CMakeLists.txt exists!" << std::endl;
      isExist.close();
      exit(-1);
    }
    isExist.close();
  }

  if (language == 'c') {
    std::cout << "[INFO] Language selected C/C++." << std::endl;
  } else {
    std::cout << "[INFO] Language selected Java." << std::endl;
  }

  if (!PJN) {
    std::string PJN_S;
    std::cout << "Project name : ";
    std::cin >> PJN_S;
    ProjectName = PJN_S.c_str();
  }

  std::ofstream cmakeFile;
  cmakeFile.open("./CMakeLists.txt", std::ios::trunc);
  switch (language) {
  case 'c':
    cmakeFile << "CMAKE_MINIMUM_REQUIRED(VERSION 3.0)" << std::endl;
    if (PJV)
      cmakeFile << "PROJECT(" << ProjectName << " VERSION " << ProjectVersion
                << ")" << std::endl;
    else
      cmakeFile << "PROJECT(" << ProjectName << ")" << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)"
              << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)" << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "SET(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/output)"
              << std::endl;
    cmakeFile << "SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}lib)"
              << std::endl;
    cmakeFile << "SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}bin)"
              << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "SET(LIBS )" << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)"
              << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)" << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src MainSrc)"
              << std::endl;
    cmakeFile << "ADD_EXECUTABLE(${PROJECT_NAME} ${MainSrc})" << std::endl;
    cmakeFile << "TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBS})" << std::endl;
    cmakeFile << "TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBS})" << std::endl;
    if (PJI) {
      cmakeFile << "INSTALL(TARGETS ${PROJECT_NAME})";
    }

    break;
  case 'j':
    cmakeFile << "CMAKE_MINIMUM_REQUIRED(VERSION 3.0)" << std::endl;
    if (PJV)
      cmakeFile << "PROJECT(" << ProjectName << " VERSION " << ProjectVersion
                << ")" << std::endl;
    else
      cmakeFile << "PROJECT(" << ProjectName << ")" << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "FIND_PACKAGE(Java REQUIRED)" << std::endl;
    cmakeFile << "INCLUDE(UseJava)" << std::endl;
    cmakeFile << std::endl;
    cmakeFile << "FILE(GLOB JavaSrc ${PROJECT_SOURCE_DIR}/src/*.java)"
              << std::endl;
    cmakeFile << "ADD_JAR(${PROJECT_NAME} ${JavaSrc} OUTPUT_DIR "
                 "${PROJECT_SOURCE_DIR}/output)"
              << std::endl;
    if (PJI) {
      cmakeFile
          << "INSTALL_JAR(${PROJECT_NAME} ${LIB_INSTALL_DIR}/${PROJECT_NAME})"
          << std::endl;
    }
    break;
  }
  cmakeFile.close();

  // Create dir
  //--------------------
  system("mkdir Build");
  system("mkdir src");
  system("mkdir include");
  system("mkdir lib");

  // Create main File
  //--------------------
  std::ofstream MainFile;
  if (language == 'c') {
    MainFile.open("src/main.cpp");
    MainFile << "#include<iostream>" << std::endl;
    MainFile << std::endl;
    MainFile << "int main(int argc, char* argv[]){" << std::endl;
    MainFile << "\tstd::cout<<\"hello, world\"<<std::endl;" << std::endl;
    MainFile << "\treturn 0;" << std::endl;
    MainFile << "}";
    MainFile.close();
  } else {
    std::string mainfilename;
    mainfilename.append("src/");
    mainfilename.append(ProjectName);
    mainfilename.append(".java");
    MainFile.open(mainfilename);
    MainFile << "public class " << ProjectName << " {" << std::endl;
    MainFile << "\tpublic static void main(String[] args){" << std::endl;
    MainFile << "\t\tSystem.out.println(\"Hello World\");" << std::endl;
    MainFile << "\t}" << std::endl;
    MainFile << "}";
  }

  // Execute Cmake
  //--------------------
  std::cout << "\n" << std::endl;
  int Cor = system("cmake -B Build .");

  printf("%s", Cor == -1 ? "[WARNING] cmake Not found!" : "\n");
  return 0;
}
