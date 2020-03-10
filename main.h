#pragma once

#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::cout;

class MessageCodec
{
public:
    virtual vector<int> encode(unsigned long, vector<int>& ) =0; //Function to encode the binary payload using RLE
    virtual vector<int> decode(unsigned long, vector<int>& ) =0; //Function to decode the RLE code back to the original binary payload
};

class Message
{
public:
    std::map<string, string> function();
    vector<int> returnArray(char* binary_payload_path);
};

class Codec : public MessageCodec
{
public:
    vector<int> encode(unsigned long size, vector<int>& byte_stream) override;
    vector<int> decode(unsigned long size, vector<int>& encoded_stream) override;
};