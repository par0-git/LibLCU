#pragma once
#include "SerializedValue.h"

namespace LCU {
	enum SerializedContainerChildType {
		OBJECT,
		CONTAINER,
	};

	class SerializedContainer;

	struct SerializedContainerChild {
		SerializedContainerChildType type;
		std::string name;
		union {
			SerializedValue* vptrObject;
			SerializedContainer* vptrContainer;
		};
	};

	class SerializedContainer {
	public:
		SerializedContainer(const rapidjson::Value& value) {
			// Make sure the value is an object
			if (!value.IsObject())
				throw Exception::SerializedContainerCreationFailure("Provided value is not an object.");

			for (rapidjson::Value::ConstMemberIterator i = value.MemberBegin(); i != value.MemberEnd(); ++i) {
				const rapidjson::Value& objectNameValue = i->name;
				const char* objectName = objectNameValue.GetString();

				const rapidjson::Value& objectValue = i->value;

				// Check if child should be container or value
				if (!objectValue.IsObject()) {
					// Make a new value
					// Push the object to the childrenValues array
					childrenValues.push_back(SerializedValue(objectValue));

					// Create a SerializedContainerChild
					SerializedContainerChild child = { SerializedContainerChildType::OBJECT, objectName };
					child.vptrObject = &childrenValues[childrenValues.size() - 1];

					printf("SerializedContainer (NewObject): %s, 0x%p\n", objectName, child.vptrObject);

					// Push the new SerializedContainerChild
					children.push_back(child);
				}
				else {
					// Make a new container
					// Push the container to the childrenContainers array
					childrenContainers.push_back(SerializedContainer(objectValue));

					// Create a SerializedContainerChild
					SerializedContainerChild child = { SerializedContainerChildType::CONTAINER, objectName };
					child.vptrContainer = &childrenContainers[childrenContainers.size() - 1];

					printf("SerializedContainer (NewContainer): %s, 0x%p\n", objectName, child.vptrContainer);

					// Push the new SerializedContainerChild
					children.push_back(child);
				}
			}
		}

		SerializedContainerChild& Get(std::string identifier) {
			for (int i = 0; i < children.size(); i++) {
				if (children[i].name == identifier)
					return children[i];
			}
			throw Exception::SerializedContainerOutOfRange("Child did not exist in array.");
		}

	std::vector<SerializedContainerChild> children;
	private:
		std::vector<SerializedContainer> childrenContainers;
		std::vector<SerializedValue> childrenValues;
	};


}