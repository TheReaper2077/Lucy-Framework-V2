#include <LucyGL/Status.h>

lgl::Status& lgl::GetStatus() {
	static lgl::Status status;
	return status;
}
