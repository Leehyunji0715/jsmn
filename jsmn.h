#ifndef __JSMN_H_//만약 JSMN_H가 선언되어있지않다면
#define __JSMN_H_//이것을 선언한다

#include <stddef.h>//요거 선언한다

#ifdef __cplusplus
extern "C" {//개념 : 전역변수 앞에 쓰이는 extern and static
#endif//위 정의사항 끝!

/**
 * JSON type identifier. Basic types are:
 * 	o Object
 * 	o Array
 * 	o String
 * 	o Other primitive: number, boolean (true/false) or null
 */
typedef enum {		//jsmntype_t 열거형(enum)!!!//아마 타입별로 번호를 나눠준것같음
	JSMN_UNDEFINED = 0,
	JSMN_OBJECT = 1,
	JSMN_ARRAY = 2,
	JSMN_STRING = 3,
	JSMN_PRIMITIVE = 4
} jsmntype_t;

enum jsmnerr {//jsmnerr 열거형
	/* Not enough tokens were provided */
	JSMN_ERROR_NOMEM = -1,
	/* Invalid character inside JSON string */
	JSMN_ERROR_INVAL = -2,
	/* The string is not a full JSON packet, more bytes expected *///packet : 통, 소포
	JSMN_ERROR_PART = -3
};

/**
//형식이 이렇게 된다는 것을 알려주는것같으메
 * JSON token description.
 * type		type (object, array, string etc.)
 * start	start position in JSON data string
 * end		end position in JSON data string
 */
typedef struct {// jsmntok_t 구조체 정의
	jsmntype_t type;//type이란 이름으로 열거형 선언
	int start;
	int end;
	int size;
#ifdef JSMN_PARENT_LINKS//만약 얘도 정의되어 있다면
	int parent;//parent도 선언
#endif
} jsmntok_t;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
typedef struct {//jsmn_parser 구조체로 정의
	unsigned int pos; /* offset상쇄하다 in the JSON string */
	unsigned int toknext; /* next token to allocate *///토큰 : 문자열을 구분할수있는 단위
	int toksuper; /* superior token node, e.g parent object or array *///상위 토큰
} jsmn_parser;

/**
 * Create JSON parser over an array of tokens(아래것 :연속적인것 -> 메모리할당을 하기위해 포인터로 선언)
 */
void jsmn_init(jsmn_parser *parser);//~~

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens, each describing
 * a single JSON object.//parse : 분석하다.
 */
int jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		jsmntok_t *tokens, unsigned int num_tokens);

#ifdef __cplusplus
}
#endif

#endif /* __JSMN_H_ */
