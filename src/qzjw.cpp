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
		if (!resp.Ready) throw runtime_error("请求无响应.");
		if (resp.StatusCode != 200) throw runtime_error("返回非 200 状态码.");
		json re_json = json::parse(resp.Content);
		string flag = re_json["flag"].get<string>();
		if (flag != "1")
		{
			string err_msg = re_json["msg"].get<string>();
		}
		token_ = re_json["token"].get<string>();
		return true;
	}

	vector<Jw::Course> Jw::GetCourses(const string& uid, int week, const string& semester)
	{
		if (token_.empty()) throw runtime_error("尚未登录.");
		stringstream url;
		url << api_prefix_
			<< "/app.do?method=getKbcxAzc&xh="
			<< uid
			<< "&xnxqid="
			<< semester
			<< "&zc="
			<< week;
		HTTP http;
		http.AddHeader("token", token_);
		auto resp = http.Get(url.str());
		if (!resp.Ready) throw runtime_error("请求无响应.");
		if (resp.StatusCode != 200) throw runtime_error("返回非 200 状态码.");
		json re_json = json::parse(resp.Content);
		vector<Course> res;
		for (auto&& ele : re_json)
		{
			int week, lesson1, lesson2;
			string t = ele["kcsj"].get<string>();
			stringstream ss;
			ss << t.substr(0, 1);
			ss >> week;
			ss.str("");
			ss << t.substr(1, 2);
			ss >> lesson1;
			ss.str("");
			ss << t.substr(2, 2);
			ss >> lesson2;

			Course c;
			c.Name = ele["kcmc"].get<string>();
			try
			{
				c.Classroom = ele["jsmc"].get<string>();
			}
			catch (...) {}
			c.Instructor = ele["jsxm"].get<string>();
			c.StartTime = ele["kssj"].get<string>();
			c.EndTime = ele["jssj"].get<string>();
			c.Schedule = ele["kkzc"].get<string>();
			c.Week = week;
			c.StartLesson = lesson1;
			c.EndLesson = lesson2;
			res.push_back(c);
		}
		return res;
	}
}
