#include "byte_stream.hh"
#include <cstdint>
#include <string>
#include <string_view>

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity )
  , error_( false )
  , closed_( false )
  , buffer_( std::string() )
  , bytes_pushed_( 0 )
  , bytes_popped_( 0 )
{}

bool Writer::is_closed() const
{
  return this->closed_;
}

void Writer::push( string data )
{
  uint64_t pushed_len;
  if ( data.length() <= this->available_capacity() ) {
    pushed_len = data.length();
  } else {
    pushed_len = this->available_capacity();
  }
  auto data_to_push = data.substr( 0, pushed_len );
  this->buffer_.append( data_to_push );
  this->bytes_pushed_ += pushed_len;
}

void Writer::close()
{
  this->closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return this->capacity_ - this->buffer_.length();
}

uint64_t Writer::bytes_pushed() const
{
  return this->bytes_pushed_;
}

bool Reader::is_finished() const
{
  return this->closed_ && this->buffer_.length() == 0;
}

uint64_t Reader::bytes_popped() const
{
  return this->bytes_popped_;
}

string_view Reader::peek() const
{
  return std::string_view { this->buffer_ };
}

void Reader::pop( uint64_t len )
{
  uint64_t poped_len;
  if ( this->buffer_.length() >= len ) {
    poped_len = len;
  } else {
    poped_len = this->buffer_.length();
  }
  this->buffer_ = this->buffer_.substr( poped_len, this->buffer_.length() );
  this->bytes_popped_ += poped_len;
}

uint64_t Reader::bytes_buffered() const
{
  return this->buffer_.length();
}
