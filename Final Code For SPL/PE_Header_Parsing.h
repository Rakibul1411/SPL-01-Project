#include<iostream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define CHAR_MAX
#define IMAGE_DOS_SIGNATURE                 0x5A4D
#define IMAGE_SIZEOF_SHORT_NAME              8
#define IMAGE_SIZEOF_SECTION_HEADER          40

char SectionName[20000][9];

char known_section_names[210][30]={
        ".AAWEBS",".apiset",".arch",".autoload_text",".bindat",".bootdat",".bss",".BSS",
        ".buildid",".CLR_UEF",".code",".cormeta",".complua",".CRT",".cygwin_dll_common",".data",
        ".DATA",".data1",".data2",".data3",".debug",".debug$F",".debug$P",".debug$S",
        ".debug$T",".drectve",".didat",".didata",".edata",".eh_fram",".export",".fasm",
        ".flat",".gfids",".giats",".gljmp",".glue_7t",".glue_7",".idata",".idlsym",
        ".impdata",".import",".itext",".ndata",".orpc",".pdata",".rdata",".reloc",
        ".rodata",".rsrc",".sbss",".script",".shared",".sdata",".srdata",".stab",
        ".stabstr",".sxdata",".text",".text0",".text1",".text2",".text3",".textbss",
        ".tls",".tls$",".udata",".vsdata",".xdata",".wixburn",".wpp_sf","BSS",
        "CODE","DATA","DGROUP","edata","idata","INIT","minATL","PAGE",
        "rdata","sdata","shared","Shared","testdata","text",".text$<name>",".data$<name>",
        ".rdata$<name>",".rsrc$<name>","/4","/14","/19","/29","/41","/48","/55","/67","/78","/89","/57","/70","/31","/45",".init",
        ".text",".text$*",".glue_7t",".glue_7",".fini",".gcc_exc",".gcc_except_table",".autoload_text",
        ".data",".data2",".data$*",".data_cygwin_nocopy",".rdata",".rdata$*",".eh_frame",".pdata",
        ".bss",".edata",".debug$S",".debug$T",".debug$F",".drectve",".idata",".idata$2",
        ".idata$3",".idata$4",".idata$5",".idata$6",".idata$7",".CRT",".endjunk",".cygwin_dll_common",
        ".rsrc",".rsrc$*",".reloc",".stab",
        ".stabstr",".debug_aranges",".debug_pubnames",".debug_info",".debug_abbrev",".debug_line",".debug_frame",".debug_str",
        ".debug_loc",".debug_macinfo",".debug_ranges",".cygheap",".btext",".bdata",".brdata",".bctors",
        ".bdtors",".rela.btext",".rela.bdata",".rela.brdata",".rela.bctors",".rela.bdtors",".bbss",".ctors",
        ".dtors",".ltext",".ldata",".lrdata",".lctors",".ldtors",".rela.ltext","rela.ldata",
        ".rela.lrdata",".rela.lctors",".rela.ldtors",".lbss","begtext","begdata","begbss","endtext","enddata","endbss"
} ;




typedef struct IMAGE_DOS_HEADER
{
    unsigned short   e_magic;
    unsigned short   e_cblp;
    unsigned short   e_cp;
    unsigned short   e_crlc;
    unsigned short   e_cparhdr;
    unsigned short   e_minalloc;
    unsigned short   e_maxalloc;
    unsigned short   e_ss;
    unsigned short   e_sp;
    unsigned short   e_csum;
    unsigned short   e_ip;
    unsigned short   e_cs;
    unsigned short   e_lfarlc;
    unsigned short   e_ovno;
    unsigned short   e_res[4];
    unsigned short   e_oemid;
    unsigned short   e_oeminfo;
    unsigned short   e_res2[10];
    unsigned long   e_lfanew;
} IMAGE_DOS_HEADER, * PIMAGE_DOS_HEADER;




typedef struct IMAGE_OPTIONAL_HEADER
{
    unsigned short    Magic;
    unsigned char     MajorLinkerVersion;
    unsigned char     MinorLinkerVersion;
    unsigned long    SizeOfCode;
    unsigned long    SizeOfInitializedData;
    unsigned long    SizeOfUninitializedData;
    unsigned long    AddressOfEntryPoint;
    unsigned long    BaseOfCode;
    unsigned long    BaseOfData;
    unsigned long    ImageBase;
    unsigned long    SectionAlignment;
    unsigned long    FileAlignment;
    unsigned short    MajorOperatingSystemVersion;
    unsigned short    MinorOperatingSystemVersion;
    unsigned short    MajorImageVersion;
    unsigned short    MinorImageVersion;
    unsigned short    MajorSubsystemVersion;
    unsigned short    MinorSubsystemVersion;
    unsigned long    Win32VersionValue;
    unsigned long    SizeOfImage;
    unsigned long    SizeOfHeaders;
    unsigned long    CheckSum;
    unsigned short    Subsystem;
    unsigned short    DllCharacteristics;
    unsigned long    SizeOfStackReserve;
    unsigned long    SizeOfStackCommit;
    unsigned long    SizeOfHeapReserve;
    unsigned long    SizeOfHeapCommit;
    unsigned long    LoaderFlags;
    unsigned long    NumberOfRvaAndSizes;

} IMAGE_OPTIONAL_HEADER, * PIMAGE_OPTIONAL_HEADER;




typedef struct IMAGE_FILE_HEADER
{
    unsigned short    Machine;
    unsigned short    NumberOfSections;
    unsigned long    TimeDateStamp;
    unsigned long    PointerToSymbolTable;
    unsigned long    NumberOfSymbols;
    unsigned short    SizeOfOptionalHeader;
    unsigned short    Characteristics;
} IMAGE_FILE_HEADER, * PIMAGE_FILE_HEADER;



typedef struct IMAGE_NT_HEADERS
{
    unsigned long  Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER OptionalHeader;
} IMAGE_NT_HEADERS, * PIMAGE_NT_HEADERS;

//section header
typedef struct __IMAGE_SECTION_HEADER
{
    unsigned char  Name[IMAGE_SIZEOF_SHORT_NAME];
    union
    {
        unsigned long    PhysicalAddress;
        unsigned long    VirtualSize;
    } Misc;
    unsigned long    VirtualAddress;
    unsigned long    SizeOfRawData;
    unsigned long    PointerToRawData;
    unsigned long    PointerToRelocations;
    unsigned long    PointerToLinenumbers;
    unsigned short    NumberOfRelocations;
    unsigned short    NumberOfLinenumbers;
    unsigned long    Characteristics;
} IMAGE_SECTION_HEADER, * PIMAGE_SECTION_HEADER;

IMAGE_DOS_HEADER   PEFILE_DOS_HEADER;
IMAGE_NT_HEADERS   PEFILE_NT_HEADERS;


unsigned long PEFILE_DOS_HEADER_EMAGIC;
unsigned long  PEFILE_DOS_HEADER_LFANEW;
unsigned long  PEFILE_NT_HEADERS_SIGNATURE;


unsigned short PEFILE_NT_HEADERS_FILE_HEADER_MACHINE;
unsigned short PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS;
unsigned short PEFILE_NT_HEADERS_FILE_HEADER_SIZEOF_OPTIONAL_HEADER;


unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_MAGIC;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_CODE;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_INITIALIZED_DATA;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_UNINITIALIZED_DATA;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_ADDRESSOF_ENTRYPOINT;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_BASEOF_CODE;
unsigned long long PEFILE_NT_HEADERS_OPTIONAL_HEADER_IMAGEBASE;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_SECTION_ALIGNMENT;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_FILE_ALIGNMENT;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_IMAGE;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_HEADERS;
unsigned short  PEFILE_NT_HEADERS_OPTIONAL_HEADER_MajorImageVersion;
unsigned long  PEFILE_NT_HEADERS_OPTIONAL_HEADER_CHECKSUM;
unsigned short  PEFILE_NT_HEADERS_OPTIONAL_HEADER_DLLCHARACTERISTICS;

PIMAGE_SECTION_HEADER PEFILE_SECTION_HEADERS;


unsigned long ParseDOSHeader(const char* _NAME, FILE* _Ppefile)
{
    const char* NAME;
    FILE* Ppefile;
    NAME = _NAME;
    Ppefile = _Ppefile;
    fseek(Ppefile, 0, SEEK_SET);
    fread(&PEFILE_DOS_HEADER, sizeof(IMAGE_DOS_HEADER), 1, Ppefile);

    PEFILE_DOS_HEADER_EMAGIC = PEFILE_DOS_HEADER.e_magic;
    PEFILE_DOS_HEADER_LFANEW = PEFILE_DOS_HEADER.e_lfanew;


    return PEFILE_DOS_HEADER_EMAGIC;



}

void ParseNTHeaders(const char* _NAME, FILE* _Ppefile,unsigned long* initializedData, unsigned long* checksum, unsigned short* dllCharacteristics, unsigned short* majorImageVersion)
{
    const char* NAME;
    FILE* Ppefile;
    NAME = _NAME;
    Ppefile = _Ppefile;
    fseek(Ppefile, PEFILE_DOS_HEADER.e_lfanew, SEEK_SET);
    fread(&PEFILE_NT_HEADERS, sizeof(PEFILE_NT_HEADERS), 1, Ppefile);

    PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_INITIALIZED_DATA = PEFILE_NT_HEADERS.OptionalHeader.SizeOfInitializedData;
    PEFILE_NT_HEADERS_OPTIONAL_HEADER_MajorImageVersion=PEFILE_NT_HEADERS.OptionalHeader.MajorImageVersion;
    PEFILE_NT_HEADERS_OPTIONAL_HEADER_CHECKSUM = PEFILE_NT_HEADERS.OptionalHeader.CheckSum;
    PEFILE_NT_HEADERS_OPTIONAL_HEADER_DLLCHARACTERISTICS = PEFILE_NT_HEADERS.OptionalHeader.DllCharacteristics;

    *initializedData = PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_INITIALIZED_DATA;
    *checksum = PEFILE_NT_HEADERS_OPTIONAL_HEADER_CHECKSUM;
    *dllCharacteristics = PEFILE_NT_HEADERS_OPTIONAL_HEADER_DLLCHARACTERISTICS;
    *majorImageVersion = PEFILE_NT_HEADERS_OPTIONAL_HEADER_MajorImageVersion;
}




int ParseSectionHeaders(const char* fileName,std::ifstream& file )
{

    IMAGE_DOS_HEADER dosHeader;
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(IMAGE_DOS_HEADER));

    unsigned long  peSignatureOffset = dosHeader.e_lfanew;

    file.seekg(peSignatureOffset, std::ios::beg);
    IMAGE_NT_HEADERS ntHeaders;
    file.read(reinterpret_cast<char*>(&ntHeaders), sizeof(IMAGE_NT_HEADERS));

    unsigned long  sectionHeadersOffset = peSignatureOffset + sizeof(unsigned long ) + sizeof(IMAGE_FILE_HEADER) + ntHeaders.FileHeader.SizeOfOptionalHeader;

    file.seekg(sectionHeadersOffset, std::ios::beg);

    int numberOfSections = ntHeaders.FileHeader.NumberOfSections;
    IMAGE_SECTION_HEADER sectionHeaders[numberOfSections];
    file.read(reinterpret_cast<char*>(&sectionHeaders), sizeof(IMAGE_SECTION_HEADER) * numberOfSections);


    for (int i = 0; i < numberOfSections; i++)
    {
        char section[8] = { 0 };
        memcpy(section, sectionHeaders[i].Name, 7);
        for(int j=0; j<8; j++)
            SectionName[i][j]=section[j];
    }

    /*for(int j=0; j<numberOfSections; j++)
        cout<<"section "<<j+1<<"->  "<<SectionName[j]<<endl;*/

    return numberOfSections;



}














