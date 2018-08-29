#include <stdio.h>
#include <stdlib.h>

#include "base/macro.h"
#include "dvb/table_factory.h"
#include "dvb/tables/application_information_table.h"

using namespace sedec;

#define USE_SECTION_FACTORY 1

int getFileLength(FILE *f)
{
  int pos;
  int end;
  pos = ftell (f);
  fseek (f, 0, SEEK_END);
  end = ftell (f);
  fseek (f, pos, SEEK_SET);
  return end;
}

int main(int argc, char *argv[])
{
  SECTION_DEBUG("***************************\n");
  SECTION_DEBUG("* Section Decoding Sample *\n");
  SECTION_DEBUG("***************************\n\n");

  FILE *fp = NULL;
  if(argc == 2) fp = fopen(argv[1], "rb");

  if(fp)
  {
    unsigned int raw_buffer_length = getFileLength(fp);
    unsigned char *raw_buffer = (unsigned char*)malloc(sizeof(unsigned char)*raw_buffer_length);
    if ( 0 < fread(raw_buffer, 1, raw_buffer_length, fp) )
    {
#if USE_SECTION_FACTORY
      base::Table *table =
          (dvb::TableFactory::CreateSection(raw_buffer));
#else
      base::Table *table =
          new dvb::ApplicationInformationTable(raw_buffer, raw_buffer_length);
#endif
      if ( table )
      {
          table->PrintTable();

          delete table;
          table = nullptr;
      }
    }
  }

  return 0;
}
