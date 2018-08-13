#include <stdio.h>
#include <stdlib.h>

#include "base/macro.h"
#include "mpegh/sections/application_information_table.h"

using namespace sedec;

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
      mpegh::ApplicationInformationTable *ait =
          new mpegh::ApplicationInformationTable(raw_buffer, raw_buffer_length);
      ait->PrintSection();

      delete ait;
      ait = nullptr;
    }
  }

  return 0;
}