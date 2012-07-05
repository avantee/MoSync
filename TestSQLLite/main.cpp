#include <newlib.h>
#include <MAUtil/Moblet.h>
#include <MAUtil/util.h>
#include <ma.h>

#include "sqlite3.h"

using namespace MAUtil;

class MyMoblet : public Moblet {
public:
	MyMoblet()
	{
		m_textHeight = 0;
		drawText("init");

		sqlite3 *db; // sqlite3 db struct
		char *zErrMsg = 0;
		int rc;

		const char *pSQL[4];
		pSQL[0] = "PRAGMA journal_mode=MEMORY;";
		pSQL[1] = "create table myTable (FirstName varchar(30), LastName varchar(30), Age smallint)";
		pSQL[2] = "insert into myTable (FirstName, LastName, Age) values ('John', 'Doe', 30)";
		pSQL[3] = "select * from myTable";

		drawText("opening db...");

		rc = sqlite3_open("testdb.sq3", &db);
		if( rc!=SQLITE_OK )
		{
			drawText("open db: error");
		}
		else
			drawText("opened db");


		sqlite3_exec(db, pSQL[0], 0, 0, 0);

		drawText("setting journal mode");

		rc = sqlite3_exec(db, pSQL[1], 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK )
		{
			drawText("create: sql error");
			drawText(zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else
			drawText("create: success");

		rc = sqlite3_exec(db, pSQL[2], 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK )
		{
			drawText("insert: sql error");
			drawText(zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else
			drawText("insert: success");

		rc = sqlite3_exec(db, pSQL[3], 0, 0, &zErrMsg);
		if( rc!=SQLITE_OK )
		{
			drawText("select: sql error");
			drawText(zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else
			drawText("select: success");

		sqlite3_close(db);
		drawText("closed db");

		drawText("press to exit...");
	}

	void pointerReleaseEvent(MAPoint2d p)
	{
		maExit(0);
	}

	void keyPressEvent(int keyCode, int nativeCode)
	{
		maExit(0);
	}

	void drawText(const String& a_text)
	{
		m_textHeight += 20;
		maSetColor(0xffffff);
		maDrawText(10, m_textHeight, a_text.c_str());
		maUpdateScreen();
		maWait(2000);
	}

	void drawText(char* a_text)
	{
		m_textHeight += 20;
		maSetColor(0xffffff);
		maDrawText(10, m_textHeight, a_text);
		maUpdateScreen();
		maWait(2000);
	}

private:
	int m_textHeight;

};

extern "C" int MAMain() {
	Moblet::run(new MyMoblet());
	return 0;
};
