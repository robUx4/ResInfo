#include "parser/parser.h"
#include "generator_stdafx.h"

static tchar_t *Size[] = {T("small"), T("normal"), T("large"), T("xlarge")};
static tchar_t *Night[] = {T("notnight"), T("night")};
static tchar_t *Density[] = {T("nodpi"), T("ldpi"), T("mdpi"), T("tvdpi"), T("hdpi"), T("xhdpi")};
static tchar_t *TouchScreen[] = {T("notouch"), T("stylus"), T("finger")};
static tchar_t *Keyboard[] = {T("keysexposed"), T("keyshidden"), T("keyssoft")};
static tchar_t *TextInput[] = {T("nokeys"), T("qwerty"), T("12key")};
static tchar_t *NavigationState[] = {T("navhidden"), T("navexposed")};
static tchar_t *NavigationMethod[] = {T("nonav"), T("dpad"), T("trackball"), T("wheel")};
static tchar_t *Aspect[] = {T("long"), T("notlong")};

#if 0
static void OutputValues(parsercontext *p, size_t size, size_t night, size_t density, size_t touchscreen, size_t keyboard, size_t textinput, size_t navstate, size_t navmethod)
{
	tchar_t Path[MAXPATH];
	textwriter Output, StringOutput;

	stprintf_s(Path, TSIZEOF(Path), T("values")
		T("-%s")
//		T("-%s")
		T("-%s")
//		T("-%s")
//		T("-%s")
//		T("-%s")
//		T("-%s")
//		T("-%s")
		,Size[size]
//		,Night[night]
		,Density[density]
//		,TouchScreen[touchscreen]
//		,Keyboard[keyboard]
//		,TextInput[textinput]
//		,NavigationState[navstate]
//		,NavigationMethod[navmethod]
		);

	FolderCreate((nodecontext*)p, Path);
	if (PathIsFolder((nodecontext*)p, Path))
	{
		tcscat_s(Path, TSIZEOF(Path), T("/resinfo.xml"));
		memset(&Output,0,sizeof(Output));
		Output.Stream = StreamOpen(p, Path, SFLAG_WRONLY|SFLAG_CREATE);

		TextElementXML(p, &Output, T("resources"));

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_size"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Size[size]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_night"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Night[night]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_density"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Density[density]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_touchscreen"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), TouchScreen[touchscreen]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_keyboard"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Keyboard[keyboard]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_textinput"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), TextInput[textinput]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_navstate"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), NavigationState[navstate]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_navmethod"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), NavigationMethod[navmethod]);
		TextElementEndData(&StringOutput, Path);

		TextElementEnd(&Output);

		StreamClose(Output.Stream);
	}
}
#endif

static void OutputArrayValues(parsercontext *p, const tchar_t *name, tchar_t *values[], size_t size)
{
	tchar_t Path[MAXPATH];
	tchar_t Value[MAXPATH];
	textwriter Output, StringOutput;
	size_t i;

	stprintf_s(Value, TSIZEOF(Value), T("res_%s"), name);

	for (i=0; i<size; ++i)
	{
		stprintf_s(Path, TSIZEOF(Path), T("values-%s"), values[i]);

		FolderCreate((nodecontext*)p, Path);
		if (PathIsFolder((nodecontext*)p, Path))
		{
			tcscat_s(Path, TSIZEOF(Path), T("/resinfo.xml"));
			memset(&Output,0,sizeof(Output));
			Output.Stream = StreamOpen(p, Path, SFLAG_WRONLY|SFLAG_CREATE);

			TextElementXML(p, &Output, T("resources"));

			TextElementBegin(&StringOutput, &Output, T("string"));
			TextAttrib(&StringOutput, T("name"), Value, TYPE_STRING);
			TcsToUpper(Path, TSIZEOF(Path), values[i]);
			TextElementEndData(&StringOutput, Path);

			TextElementEnd(&Output);

			StreamClose(Output.Stream);
		}
	}
}

int main(void)
{
    parsercontext p;
	//size_t size, night, density, touchscreen, keyboard, textinput, navstate, navmethod;

	// Core-C init phase
	ParserContext_Init(&p,NULL,NULL,NULL);
	StdAfx_Init((nodemodule*)&p);
	//ProjectSettings((nodecontext*)&p);

	OutputArrayValues(&p, T("size"), Size, sizeof(Size)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("night"), Night, sizeof(Night)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("density"), Density, sizeof(Density)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("touchscreen"), TouchScreen, sizeof(TouchScreen)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("keyboard"), Keyboard, sizeof(Keyboard)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("textinput"), TextInput, sizeof(TextInput)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("navstate"), NavigationState, sizeof(NavigationState)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("navmethod"), NavigationMethod, sizeof(NavigationMethod)/sizeof(tchar_t*));
	OutputArrayValues(&p, T("aspect"), Aspect, sizeof(Aspect)/sizeof(tchar_t*));

#if 0
	for (size = 0; size < sizeof(Size)/sizeof(tchar_t*); ++size)
	{
		for (night = 0; night < sizeof(Night)/sizeof(tchar_t*); ++night)
		{
			for (density = 0; density < sizeof(Density)/sizeof(tchar_t*); ++density)
			{
				for (touchscreen = 0; touchscreen < sizeof(TouchScreen)/sizeof(tchar_t*); ++touchscreen)
				{
					for (keyboard = 0; keyboard < sizeof(Keyboard)/sizeof(tchar_t*); ++keyboard)
					{
						for (textinput = 0; textinput < sizeof(TextInput)/sizeof(tchar_t*); ++textinput)
						{
							for (navstate = 0; navstate < sizeof(NavigationState)/sizeof(tchar_t*); ++navstate)
							{
								for (navmethod = 0; navmethod < sizeof(NavigationMethod)/sizeof(tchar_t*); ++navmethod)
								{
									OutputValues(&p, size, night, density, touchscreen, keyboard, textinput, navstate, navmethod);
								}
							}
						}
					}
				}
			}
		}
	}
#endif

	// Core-C ending
	StdAfx_Done((nodemodule*)&p);
	ParserContext_Done(&p);

	return 0;
}
