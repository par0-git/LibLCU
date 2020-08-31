#pragma once

// Begin a scope for managing a JSON Object<->C++ Class transfer.
#define JSON_CLASS_BEGIN(input, output) { nlohmann::json& _json_input_ = input; decltype(output)& _class_output_ = output;

#define JSON_CLASS_BEGIN_SAFE(input, output) try { nlohmann::json& _json_input_ = input; decltype(output)& _class_output_ = output;

// Copy a variable to / from a JSON object.
#define JSON_TO_CLASS_MEMBER(json_member, class_member) _class_output_.class_member = _json_input_ json_member.get<decltype(_class_output_.class_member)>();
#define JSON_FROM_CLASS_MEMBER(class_member, json_member) _json_input_ json_member = _class_output_.class_member;

// End a scope for managing a JSON Object<->C++ Class transfer.
#define JSON_CLASS_END() }
