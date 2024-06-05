#include "reassembler.hh"
#include <iostream>
#include <ostream>

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  auto& writer = this->output_.writer();
  // if the data is too large, drop it directly
  if ( data.length() > ( writer.available_capacity() - this->bytes_pending_ ) ) {
    return;
  }
  // if the data is expecting data, write it in the bytestream
  if ( first_index == this->expecting_index_ ) {
    writer.push( data );
    if ( is_last_substring ) {
      writer.close();
    }
  } else {
    // if not, buffer it in the assembler
    // how to buffer it? what data structure should I use?
  }
}

uint64_t Reassembler::bytes_pending() const
{
  return this->bytes_pending_;
}
