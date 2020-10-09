#pragma once
#include "SerializedValue.h"

namespace LCU {
	enum SerializedContainerChildType {
		OBJECT,
		CONTAINER,
	};

	struct SerializedContainerChild {
		SerializedContainerChildType type;
		union {
			SerializedValue vObject;
			SerializedContainer vContainer;
		};
	};

	class SerializedContainer {
	public:
		SerializedContainer(std::string containerName) {
			name = containerName;
		}

		SerializedContainerChild& Get() {

		}
	private:
		std::string name;
		std::vector<SerializedContainerChild> children;
	};
}