#include "byte_stream.hh"
#include <algorithm>
#include <cstdint>

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), error_( false ), data_( "" ), closed_( false ), bytes_popped_( 0 ), bytes_pushed_( 0 )
{}

void Writer::push( string data )
{
  if ( closed_ ) {
    return;
  }
  uint64_t size_to_push = min( available_capacity(), data.size() );
  data_ += data.substr( 0, size_to_push );
  bytes_pushed_ += size_to_push;
}

void Writer::close()
{
  closed_ = true;
}

bool Writer::is_closed() const
{
  return closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - data_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

string_view Reader::peek() const
{
  return data_;
}

void Reader::pop( uint64_t len )
{
  data_ = data_.substr( len, data_.size() - len );
  bytes_popped_ += len;
}

bool Reader::is_finished() const
{
  return closed_ && data_.size() == 0;
}

uint64_t Reader::bytes_buffered() const
{
  return data_.size();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_;
}
