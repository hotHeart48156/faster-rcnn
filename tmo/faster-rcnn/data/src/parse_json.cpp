#include <parse_json.h>
#include "voc_xml_data_model.h"
#include <string>
#include <daw/daw_read_file.h>
#include <daw/json/daw_from_json.h>
void parse(::std::string filename)
{
    auto data = *daw::read_file(filename.data());
    auto  const c = daw::json::from_json<Object>(
    std::string_view(data.data(),data.size()));
}
