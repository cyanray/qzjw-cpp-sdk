#include "qzjw.h"
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <CURLWrapper.h>
using namespace Cyan;
using std::stringstream;
using std::runtime_error;
using namespace nlohmann;

namespace cyanray
{
	bool Jw::Login(const string& uid, const string& pwd)
	{
		stringstream url;
		url << api_prefix_
			<< "/app.do?method=authUser&xh="
			<< uid
			<< "&pwd="
			<< pwd;
		HTTP http;
		auto resp = http.Get(url.str());
		if (!resp.Ready) throw runtime_error("��������Ӧ.");
		if (resp.StatusCode != 200) throw runtime_error("���ط� 200 ״̬��.");
		json re_json = json::parse(resp.Content);
		string flag = re_json["flag"].get<string>();
		if(flag != "1")
		{
			string err_msg = re_json["msg"].get<string>();
		}
		token_ = re_json["token"].get<string>();
		return true;
	}

	vector<Jw::Course> Jw::GetCourses(const string&, int week, const string& semester)
	{
	}

}
