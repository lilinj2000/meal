AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = meal
meal_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc

meal_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(RAPIDJSON_CPPFLAGS) \
		$(JSON_CPPFLAGS) \
		$(ZOD_CPPFLAGS)


meal_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(JSON_LIBADD) \
	$(ZOD_LIBADD)


meal_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh \
	Log.hh \
	Server.hh

EXTRA_DIST = env.sh meal.cfg log.cfg

mealdir = $(bindir)
meal_DATA = $(EXTRA_DIST)

