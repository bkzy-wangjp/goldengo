#ifndef __GOLDEN_H__
#define __GOLDEN_H__

#ifdef WIN32
#ifdef GOLDENAPI_EXPORTS
#  define GOLDENAPI extern "C" __declspec(dllexport)
#else
#  define GOLDENAPI extern "C" __declspec(dllimport)
#endif

#define GOLDENAPI_CALLRULE _stdcall
#endif //WIN32

#ifdef SOLARIS
#define GOLDENAPI extern "C" 
#define GOLDENAPI_CALLRULE 
#endif //SOLARIS


#ifndef For_Classof
#define Golden_Mark_Classof        0x0F
#define Golden_Len_Classof         4
#define Golden_Base_Datetime_Type  0x10
#endif

/// ����ѭ�����ձ������������糬���˳��Դ������ޱ����ʹ���������
#define Golden_CycRev_Max_Times    20   

/// ��ά���궨��
typedef struct _GOLDEN_COORDINATE
{
  float x;
  float y;
} GOLDEN_COORDINATE;

typedef unsigned char       golden_byte;          /// ���ֽ���ֵ
typedef char                golden_int8;          /// 8λ����
typedef unsigned char       golden_uint8;         /// 8λ������
typedef short               golden_int16;         /// 16λ����
typedef unsigned short      golden_uint16;        /// 16λ������
typedef int                 golden_int32;         /// 32λ����
typedef unsigned int        golden_uint32;        /// 32λ������
typedef long long           golden_int64;         /// 64λ����
typedef unsigned long long  golden_uint64;        /// 64λ������
typedef short               golden_float16;       /// 16λ������
typedef float               golden_float32;       /// 32λ������
typedef double              golden_float64;       /// 64λ������
typedef GOLDEN_COORDINATE   golden_coordinate;    /// ��ά����
typedef unsigned int        golden_error;         /// ������ֵ
typedef void*               golden_datagram_handle;
/// 0x0200 ���ڵ�ϵͳ����������
enum GOLDEN_QUALITY
{
  GOLDEN_Q_GOOD     = 0,    // ����
  GOLDEN_Q_NODATA   = 1,    // ������
  GOLDEN_Q_CREATED  = 2,    // ����
  GOLDEN_Q_SHUTDOWN = 3,    // ͣ��
  GOLDEN_Q_CALCOFF  = 4,    // ����ֹͣ
  GOLDEN_Q_BAD      = 5,    // ����
  GOLDEN_Q_DIVBYZERO= 6,    // �����
  GOLDEN_Q_REMOVED  = 7,    // �ѱ�ɾ��
  GOLDEN_Q_OPC      = 256,  // ��0x0100��0x01FFΪOPC������
  GOLDEN_Q_USER     = 512   // �������루����֮��Ϊ�û��Զ���
};

/// ����ѡ��
enum GOLDEN_OPTION
{
  GOLDEN_O_AUTOCONN = 1,    // �Զ�����
};

///�����¼�
enum GOLDEN_EVENT_TYPE
{
  GOLDEN_E_DATA          = 0,   // ����
  GOLDEN_E_DISCONNECT    = 1,   // ���ӶϿ�
  GOLDEN_E_RECOVERY      = 2,   // ���ӻָ�
};

/// Ϊ���������ӻ�ȥ�� UPDATE ��־��U Ϊ true ���� UPDATE ��־������ȥ�� UPDATE ��־
#define GOLDEN_QUALITY_MODIFY_UPDATE_FLAG(Q, U)   (U) ? (Q) |= 0x8000 : (Q) &= 0x7FFF;

/// �����������ж��¼��Ƿ��޸Ĺ�
#define GOLDEN_QUALITY_IS_UPDATED(Q)              ( (Q) & 0x8000 )

/// ��ò����� UPDATE ��־��������
#define GOLDEN_QUALITY_WITHOUT_FLAG(Q)            ( (Q) & 0x7FFF )

/// OPCЭ����������Ч���ݵ�����
#define GOLDEN_QUALITY_OPC_GOOD                   0xC0

/// ��OPCЭ���ȡ�������룬ʹ�ô˺�ת��ΪGOLDEN�ж�Ӧ��������
#define GOLDEN_QUALITY_FROM_OPC(OPC_Q)            ( GOLDEN_QUALITY_OPC_GOOD == (OPC_Q) ? GOLDEN_Q_GOOD : (OPC_Q) & 0xFF | GOLDEN_Q_OPC )

/// �ж�GOLDEN�е��������Ƿ�����OPCЭ�鷶Χ
#define GOLDEN_QUALITY_IS_OPC(Q)                  ( GOLDEN_QUALITY_WITHOUT_FLAG(Q) >= GOLDEN_Q_OPC && GOLDEN_QUALITY_WITHOUT_FLAG(Q) < GOLDEN_Q_USER )

/// GOLDEN������OPCЭ�鷶Χ�������룬ʹ�ô˺껹ԭΪOPCԭʼ������
#define GOLDEN_QUALITY_TO_OPC(Q)                  ( GOLDEN_Q_GOOD == GOLDEN_QUALITY_WITHOUT_FLAG(Q) ? GOLDEN_QUALITY_OPC_GOOD : (Q) & 0xFF )

/// ���������ж���Ӧ���¼��Ƿ�������Ч
#define GOLDEN_QUALITY_IS_VALID(Q)                ( GOLDEN_Q_GOOD == GOLDEN_QUALITY_WITHOUT_FLAG(Q) )

/// ���������ж���Ӧ���¼��Ƿ�ɾ��
#define GOLDEN_QUALITY_IS_REMOVED(Q)              ( GOLDEN_Q_REMOVED == GOLDEN_QUALITY_WITHOUT_FLAG(Q) )

/// ϵͳ��������
enum GOLDEN_CONST
{ 
  GOLDEN_TAG_SIZE = 80,                                 /// ��ǩ������ռ���ֽ�����
  GOLDEN_DESC_SIZE = 100,                               /// ��ǩ������ռ���ֽ�����
  GOLDEN_UNIT_SIZE = 20,                                /// ��ǩ�㵥λռ���ֽ�����
  GOLDEN_USER_SIZE = 20,                                /// �û���ռ���ֽ�����
  GOLDEN_SOURCE_SIZE = 256,                             /// ��ǩ������Դռ���ֽ�����
  GOLDEN_INSTRUMENT_SIZE = 50,                          /// ��ǩ�������豸ռ���ֽ�����
  GOLDEN_LOCATIONS_SIZE = 5,                            /// �ɼ���ǩ��λַ������
  GOLDEN_USERINT_SIZE = 2,                              /// �ɼ���ǩ���û��Զ�������������
  GOLDEN_USERREAL_SIZE = 2,                             /// �ɼ���ǩ���û��Զ��帡����������
  GOLDEN_EQUATION_SIZE = 2036,                          /// �����ǩ�㷽��ʽռ���ֽ�����
  GOLDEN_TYPE_NAME_SIZE = 21,                           /// �Զ�����������ռ���ֽ�����
  GOLDEN_PACK_OF_SNAPSHOT = 0,                          /// �¼����ձ����ֽڿռ䡣
  GOLDEN_PACK_OF_POINT = 5,                             /// ��ǩ�㱸���ֽڿռ䡣
  GOLDEN_PACK_OF_BASE_POINT = 74,                       /// ������ǩ�㱸���ֽڿռ䡣
  GOLDEN_PACK_OF_SCAN = 164,                            /// �ɼ���ǩ�㱸���ֽڿռ䡣
  GOLDEN_PACK_OF_CALC = 0,                              /// �����ǩ�㱸���ֽڿռ䡣
  GOLDEN_FILE_NAME_SIZE = 64,                           /// �ļ����ַ����ֽڳ���
  GOLDEN_PATH_SIZE = 1024 - 4 - GOLDEN_FILE_NAME_SIZE,  /// ·���ַ����ֽڳ���
  GOLDEN_MAX_USER_COUNT = 100,                        /// ����û�����
  GOLDEN_MAX_AUTH_COUNT = 100,                          /// ����������Ӷθ���
  GOLDEN_MAX_BLACKLIST_LEN = 100,                       /// ���Ӻ�������󳤶�
  GOLDEN_MAX_SUBSCRIBE_SNAPSHOTS = 1000,                /// ������������Ŀ�������
  GOLDEN_API_SERVER_DESCRIPTION_LEN = 512,              /// API_SERVER�У�decription�����ֶεĳ���

  GOLDEN_MIN_EQUATION_SIZE = 480,                       /// �������Ⱥ�ķ���ʽռ���ֽ���
  GOLDEN_PACK_OF_MIN_CALC = 19,                          /// �������Ⱥ�ļ����ǩ�㱸���ֽڿռ�
  GOLDEN_MAX_EQUATION_SIZE = 62 * 1024,                  /// ��󳤶ȵķ���ʽռ���ֽ���
  GOLDEN_PACK_OF_MAX_CALC = 64 * 1024 - GOLDEN_MAX_EQUATION_SIZE - 12,  /// ��󳤶ȵļ����ǩ�㱸���ֽڿռ�
  GOLDEN_MAX_JSON_SIZE = 16 * 1024,                      /// �����json�ַ�������󳤶�

  GOLDEN_OUTPUT_PLUGIN_LIB_VERSION_LENGTH = 0x40,               // ������������������汾�ų��� 64  Bytes
  GOLDEN_OUTPUT_PLUGIN_LIB_NAME_LENGTH = 0x80,                  // ������������������������    128 Bytes
  GOLDEN_OUTPUT_PLUGIN_ACTOR_NAME_LENGTH = 0x80,                // �������������ִ��ʵ������    128 Bytes
  GOLDEN_OUTPUT_PLUGIN_NAME_LENGTH = 0xFF,                      // ����������������������      255 Bytes
  GOLDEN_OUTPUT_PLUGIN_DIR_LENGTH = 0xFF,                       // �������������·������        255 Bytes
  GOLDEN_PER_OF_USEFUL_MEM_SIZE = 10,					///��ʷ���ݻ���/����ʷ���ݻ���/blob����ʷ���ݻ���/�ڴ��С����ռ�����ڴ�ٷֱ�ֵռ�õ��ֽ���
};


typedef char golden_tag_string[GOLDEN_TAG_SIZE];
typedef char golden_desc_string[GOLDEN_DESC_SIZE];
typedef char golden_unit_string[GOLDEN_USER_SIZE];
typedef char golden_source_string[GOLDEN_SOURCE_SIZE];
typedef char golden_instrument_string[GOLDEN_INSTRUMENT_SIZE];
typedef char golden_equation_string[GOLDEN_EQUATION_SIZE];
typedef char golden_type_name_string[GOLDEN_TYPE_NAME_SIZE];
typedef char golden_filename_string[GOLDEN_FILE_NAME_SIZE];
typedef char golden_path_string[GOLDEN_PATH_SIZE];
typedef char golden_min_equation_string[GOLDEN_MIN_EQUATION_SIZE];
typedef char golden_json_string[GOLDEN_MAX_JSON_SIZE];

/// ��ǩ����ֵ���ͣ������˱�ǩ����ֵ��ռ�õĴ洢�ֽ�����
enum GOLDEN_TYPE
{ 
  GOLDEN_BOOL,      /// �������ͣ�0ֵ��1ֵ��
  GOLDEN_UINT8,     /// �޷���8λ������ռ��1�ֽڡ�
  GOLDEN_INT8,      /// �з���8λ������ռ��1�ֽڡ�
  GOLDEN_CHAR,      /// ���ֽ��ַ���ռ��1�ֽڡ�
  GOLDEN_UINT16,    /// �޷���16λ������ռ��2�ֽڡ�
  GOLDEN_INT16,     /// �з���16λ������ռ��2�ֽڡ�
  GOLDEN_UINT32,    /// �޷���32λ������ռ��4�ֽڡ�
  GOLDEN_INT32,     /// �з���32λ������ռ��4�ֽڡ�
  GOLDEN_INT64,     /// �з���64λ������ռ��8�ֽڡ�
  GOLDEN_REAL16,    /// 16λ��������ռ��2�ֽڡ�
  GOLDEN_REAL32,    /// 32λ�����ȸ�������ռ��4�ֽڡ�
  GOLDEN_REAL64,    /// 64λ˫���ȸ�������ռ��8�ֽڡ�
  GOLDEN_COOR,      /// ��ά���꣬����x��y����ά�ȵĸ�������ռ��8�ֽڡ�
  GOLDEN_STRING,    /// �ַ��������Ȳ������洢ҳ���С��
  GOLDEN_BLOB,      /// ���������ݿ飬ռ���ֽڲ������洢ҳ���С��
  GOLDEN_NAMED_T,   /// �Զ������ͣ����û�����ʱȷ���ֽڳ��ȡ�
  //---------------------------------------------------------/
  GOLDEN_DATETIME,  /// ʱ���ʽ����
};

#define GOLDEN_TYPE_COUNT (GOLDEN_DATETIME + 1)

#define GOLDEN_TYPE_IS_NORMAL(TYPE)    ( (TYPE == GOLDEN_STRING || TYPE == GOLDEN_BLOB) ? false : true )

/// ��ǩ����𣬾����˱�ǩ�������Щ��չ���ԡ���ǩ�����ͬʱ�߱������������Զ���33����ǩ�����
enum GOLDEN_CLASS
{ 
  GOLDEN_BASE = 0,    /// ������ǩ�㣬��������ǩ����ڻ�����ǩ������Լ�����չ�Լ������Լ���
  GOLDEN_SCAN = 1,    /// �ɼ���ǩ�㡣
  GOLDEN_CALC = 2,    /// �����ǩ�㡣
  GOLDEN_ALARM = 4,   /// ������ǩ�㡣
};

/// �ж���ǩ���Ƿ�ɼ���ǩ��
#define GOLDEN_CLASS_IS_SCAN(CLASSOF)    (CLASSOF & GOLDEN_SCAN)

/// �ж���ǩ���Ƿ�����ǩ��
#define GOLDEN_CLASS_IS_CALC(CLASSOF)    (CLASSOF & GOLDEN_CALC)

/// �ж���ǩ���Ƿ񱨾���ǩ��
#define GOLDEN_CLASS_IS_ALARM(CLASSOF)    (CLASSOF & GOLDEN_ALARM)

/// �����ǩ�㴥�����ơ�
enum GOLDEN_TRIGGER
{ 
  GOLDEN_NULL_TRIGGER,        /// �޴���
  GOLDEN_EVENT_TRIGGER,       /// �¼�����
  GOLDEN_TIMER_TRIGGER,       /// ���ڴ���
  GOLDEN_FIXTIME_TRIGGER,     /// ��ʱ����
};

/// ������ʱ����ο���
enum GOLDEN_TIME_COPY
{ 
  GOLDEN_CALC_TIME,             ///���ü���ʱ��
  GOLDEN_LATEST_TIME,           ///���������ǩ��ʱ��
  GOLDEN_EARLIEST_TIME,         ///���������ǩ��ʱ��
};

/// ��ǩ�������������ʽ
enum GOLDEN_SEARCH_SORT
{ 
  GOLDEN_SORT_BY_TABLE,     /// ���Ȱ�����������ͬһ�����ڵı�ǩ��֮�䰴��ǩ����������
  GOLDEN_SORT_BY_TAG,       /// �Ա�ǩ����������
  GOLDEN_SORT_BY_ID,        /// �Ա�ǩ��ID����
};

/// ��ʷ����������ʽ
enum GOLDEN_HIS_MODE 
{
  GOLDEN_NEXT,            ///Ѱ����һ����������ݣ�
  GOLDEN_PREVIOUS,        ///Ѱ����һ����������ݣ�
  GOLDEN_EXACT,           ///ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
  GOLDEN_INTER,           ///ȡָ��ʱ����ڲ�ֵ���ݡ�
};

enum GOLDEN_SEARCH_MASK
{
  GOLDEN_SEARCH_NULL,                               //��ʹ���κα�ǩ��������Ϊ��������
  GOLDEN_SEARCH_COMPDEV,                            //ʹ��ѹ��ƫ����Ϊ��������
  GOLDEN_SEARCH_COMPMAX,                            //���ѹ�����
  GOLDEN_SEARCH_COMPMIN,                            //��Сѹ�����
  GOLDEN_SEARCH_EXCDEV,                             //����ƫ��
  GOLDEN_SEARCH_EXCMAX,                             //���������
  GOLDEN_SEARCH_EXCMIN,                             //��С������
  GOLDEN_SEARCH_SUMMARY,                            //�Ƿ����
  GOLDEN_SEARCH_MIRROR,                             //�Ƿ���
  GOLDEN_SEARCH_COMPRESS,                           //�Ƿ�ѹ��
  GOLDEN_SEARCH_STEP,                               //�Ƿ��Ծ
  GOLDEN_SEARCH_SHUTDOWN,                           //�Ƿ�ͣ����д
  GOLDEN_SEARCH_ARCHIVE,                            //�Ƿ�鵵
  GOLDEN_SEARCH_CHANGER,                            //�޸���
  GOLDEN_SEARCH_CREATOR,                            //������
  GOLDEN_SEARCH_LOWLIMIT,                           //��������
  GOLDEN_SEARCH_HIGHLIMIT,                          //��������
  GOLDEN_SEARCH_TYPICAL,                            //����ֵ
  GOLDEN_SEARCH_CHANGEDATE,                         //�޸�ʱ��
  GOLDEN_SEARCH_CREATEDATE,                         //����ʱ��
  GOLDEN_SEARCH_DIGITS,                             //��ֵλ��
  GOLDEN_SEARCH_COMPDEVPERCENT,                     //ѹ��ƫ��ٷֱ�
  GOLDEN_SEARCH_EXCDEVPERCENT,                      //����ƫ��ٷֱ�

  GOLDEN_SEARCH_SCAN_BEGIN,                         //�������ã�������Ϊ��������
  GOLDEN_SEARCH_SCAN,                               //�Ƿ�ɼ�
  GOLDEN_SEARCH_LOCATION1,                          //�豸λַ1
  GOLDEN_SEARCH_LOCATION2,                          //�豸λַ2
  GOLDEN_SEARCH_LOCATION3,                          //�豸λַ3
  GOLDEN_SEARCH_LOCATION4,                          //�豸λַ4
  GOLDEN_SEARCH_LOCATION5,                          //�豸λַ5
  GOLDEN_SEARCH_USERINT1,                           //�Զ�������1
  GOLDEN_SEARCH_USERINT2,                           //�Զ�������2
  GOLDEN_SEARCH_USERREAL1,                          //�Զ��嵥���ȸ�����1
  GOLDEN_SEARCH_USERREAL2,                          //�Զ��嵥���ȸ�����2
  GOLDEN_SEARCH_SCAN_END,                           //�������ã�������Ϊ��������

  GOLDEN_SEARCH_CALC_BEGIN,                         //�������ã�������Ϊ��������
  GOLDEN_SEARCH_EQUATION,                           //����ʽ
  GOLDEN_SEARCH_TRIGGER,                            //���㴥������
  GOLDEN_SEARCH_TIMECOPY,                           //������ʱ����ο�
  GOLDEN_SEARCH_PERIOD,                             //��������
  GOLDEN_SEARCH_CALC_END,                           //�������ã�������Ϊ��������
};

enum GOLDEN_API_OPTION
{
  GOLDEN_API_AUTO_RECONN,     /// api �������жϺ��Ƿ��Զ�����, 0 ��������1 ������Ĭ��Ϊ 0 ������
  GOLDEN_API_CONN_TIMEOUT,     /// api ���ӳ�ʱֵ���ã���λ���룩,0 ����ģʽ�����޵ȴ���Ĭ��Ϊ0
}; 

enum GOLDEN_PROCESS_NAME
{
  GOLDEN_PROCESS_FIRST = 1, 
  GOLDEN_PROCESS_HISTORIAN = GOLDEN_PROCESS_FIRST, 
  GOLDEN_PROCESS_EQUATION, 
  GOLDEN_PROCESS_BASE, 
  GOLDEN_PROCESS_LAST, 
}; 

/// ������
enum GOLDEN_BIG_JOB_NAME
{
  /// ��ʷ���ݷ���
  GOLDEN_MERGE          = 1,            ///�ϲ������ļ������ļ���
  GOLDEN_ARRANGE        = 2,            ///����浵�ļ�����������л���ɺϲ�
  GOLDEN_REINDEX        = 3,            ///�ؽ�������
  GOLDEN_BACKUP         = 4,            ///���ݡ�
  GOLDEN_REACTIVE       = 5,            ///����Ϊ��浵��
  GOLDEN_MOVE_ARCHIVE   = 6,            ///�ƶ��浵�ļ�
  GOLDEN_CONVERT_INDEX  = 7,            ///ת���浵�ļ���������
  /// ����ʽ���� 
  GOLDEN_COMPUTE  = 11,                 ///��ʷ����
  /// ��ǩ����Ϣ����
  GOLDEN_UPDATE_TABLE = 21,             ///�޸ı�����
  GOLDEN_REMOVE_TABLE = 22,             ///ɾ����
};

enum GOLDEN_POINT_MIRROR
{
	GOLDEN_POINT_OFF = 0,
	GOLDEN_POINT_SEND_RECV = 1,
    GOLDEN_POINT_RECV = 2,
	GOLDEN_POINT_SEND=3
};


/// ��ǩ�����������Լ���
typedef struct _GOLDEN_TABLE
{
  /**
  * ���Ψһ��ʶ��
  * ��1��ʼ��������Ϊֹ��
  */
  int  id;
  /**
  * �����͡�
  * ��ʱ������;��
  */
  int  type;
  /** �����ơ�
  *  ��������
  *  1����һ���ַ�������26����ĸ֮һ������0-9֮һ��
  *  2��������ʹ�ÿ����ַ������绻�з����Ʊ����
  *  3��������ʹ�������ַ���'*'��'''��'?'��';'��'{'��'}'��'['��']'��'|'��'\'��'`'��'''��'"'��'.'����
  *  4���ֽڳ��Ȳ�Ҫ���� GOLDEN_TAG_SIZE�����������ϵͳ���Զ���������ַ��ضϡ�
  */
  char name[GOLDEN_TAG_SIZE];
  /**
  *  ��������
  *  ȱʡֵ�����ַ�����
  *  �ֽڳ��Ȳ�Ҫ���� GOLDEN_DESC_SIZE������Ĳ��ֻᱻ�ضϡ�
  */
  char desc[GOLDEN_DESC_SIZE];
} GOLDEN_TABLE;

/// ������ǩ�����Լ���
/**
 * ������ǩ�����Լ���8�ֽڶ����������ռ��512�ֽڡ�
 */
typedef struct _GOLDEN_POINT
{
  /**
  *  ��ǩ�����ơ�
  *  �����ڱ���Ψһ��ʶһ����ǩ�㣻
  *  �����������޸ģ�
  *  ��������
  *  1����һ���ַ�������26����ĸ֮һ������0-9֮һ����"_"��"%"��
  *  2��������ʹ�ÿ����ַ������绻�з����Ʊ����
  *  3��������ʹ�������ַ���'*'��'''��'?'��';'��'('��')'��'{'��'}'��'['��']'��'|'��'\'��'`'��'''��'"'��'.'����
  *  4���ֽڳ��Ȳ�Ҫ����79�����������ϵͳ���Զ���������ַ��ضϡ�
  */
  char tag[GOLDEN_TAG_SIZE];
  /**
  *  ȫ��Ψһ��ʶ��
  *  ֻ�����ԣ�������ǩ��ʱϵͳ���Զ�Ϊ��ǩ������Ψһ��ʶ������ǩ��ID����ǩ��IDһ���������������ġ�
  */
  int id;
  /**
  *  ��ǩ�����ֵ���͡�
  *  ֻ�����ԣ��ڴ�����ǩ��ʱָ����
  */
  int type;
  /**
  *  ��ǩ��������ID��
  */
  int table;
  /**
  *  �йر�ǩ������������֡�
  *  �ֽڳ��Ȳ�Ҫ����99������Ĳ��ֻᱻ�ضϡ�
  */
  char desc[GOLDEN_DESC_SIZE];
  /**
  *  ���̵�λ��
  *  �ֽڳ��Ȳ�Ҫ����19������Ĳ��ֻᱻ�ضϡ�
  */
  char unit[GOLDEN_UNIT_SIZE];
  /**
  *  �Ƿ�浵��
  *  ȱʡֵ��ON��1��
  *  ON��1��ʾ�浵��OFF��0��ʾ���浵��
  */
  golden_byte archive;
  /**
  *  ��ֵλ����
  *  ȱʡֵ��-5��
  *  ��Χ��>=-20��<=10��
  *  ����������ֵ����ʾ��ʽ��
  *  ���Ϊ0����������ʾ��ֵ��С��λ�������Ϊ��������ʾ��ֵ����Чλ����
  */
  short digits;
  /**
  *  ͣ��״̬�֣�Shutdown��
  *  ȱʡֵ��0��
  *  ����õ���ͣ��״̬���Ƿ�дͣ��״ֵ̬��
  *  1 ��ʾ��д��0 ��ʾ����д��
  */
  golden_byte shutdown;
  /**
  *  �������ޡ�
  *  ȱʡֵ��0��
  *  ��λ����ǩ�㹤�̵�λ��
  */
  float lowlimit;
  /**
  *  �������ޡ�
  *  ȱʡֵ��100��
  *  ��λ����ǩ�㹤�̵�λ��
  */
  float highlimit;
  /**
  *  �Ƿ��Ծ��
  *  ȱʡֵ��OFF��0��
  *  �����Ծ������м�ֵ�ļ������ý��ݻ����������ڲ�ֵ�滻��
  *  ȱʡ����¸�����ΪOFF�����м�ֵ�ļ��������ڲ�ֵ�滻��
  *  ���������ΪON�����м�ֵ����ֵͬǰһ���м�¼����ֵ��ͬ��
  *  ����ʷ���ݼ����У������ÿ��ܱ��ⲿ����Ľ�Ծ���ظ��ǡ�
  */
  golden_byte step;
  /**
  *  ����ֵ��
  *  ȱʡֵ��50��
  *  ���ڵ����������ޣ�С�ڵ����������ޡ�
  */
  float typical;
  /**
  *  �Ƿ�ѹ����
  *  ȱʡֵ��ON��1��
  *  ��������Ա��رգ�OFF��0�����κε������ݴ洢������Server�����ݶ��ᱻ�ύ����ʷ���ݿ⣻����ON��1����ֻ������ѹ�����������ݲŻᱻ�ύ����ʷ���ݿ⡣
  *  ��Ҫ�ֹ�¼��ı�ǩ��Ӧ�ý�����������ΪOFF��0��
  */
  golden_byte compress;
  /**
  *  ѹ��ƫ�
  *  ��λ����ǩ�㹤�̵�λ��
  *  ȱʡֵ��1��
  *  �����µ���ֵ���ύ�����ݴ洢������Server���������һ�����ύ����ʷ���ݿ����ֵ��ʼ����ֵ������ѹ��ƫ���⣬����һ�����ύ�����ݴ洢������Server����ֵ����Ϊ�ؼ���ֵ��
  *  ��������[ѹ��ƫ��ٷֱȣ�the percent of compression deviation��]���Ժ�����ͬ�������������̣�high
  *  limit - low limit���İٷֱȼ�[ѹ��ƫ��ٷֱȣ�the percent of compression
  *  deviation��]���Ե�ֵ��
  *  �Ը����Ե��޸Ľ����¶�[ѹ��ƫ��ٷֱȣ�the percent of compression
  *  deviation��]���޸ģ�ͬ������[ѹ��ƫ��ٷֱȣ�the percent of compression
  *  deviation��]���޸�Ҳ���޸ĸ����ԣ��������ͬʱ���޸ģ�[ѹ��ƫ��ٷֱȣ�the percent of compression
  *  deviation��]���и��ߵ�����Ȩ��
  */
  float compdev;
  /**
  *  ѹ��ƫ��ٷֱȡ�
  *  ��λ���ٷֱȣ�
  *  �ο���[ѹ��ƫ��]��
  */
  float compdevpercent;
  /**
  *  ���ѹ�������
  *  ��λ���룻
  *  ȱʡֵ��28800��
  *  ���ĳ����ֵ����һ�����ύ����ʷ���ݿ����ֵ��ʱ�������ڻ�������ѹ������������Ƿ�����ѹ������������ֵ��Ӧ�ñ���Ϊ�ؼ���ֵ�Ӷ����ύ����ʷ���ݿ�����ݶ��У�
  *  ���ݿ���������ǩ����ʱ�����п��ܳ���������ֵ����Ϊ���ݴ洢������Server���ܳ�ʱ����ղ����ύ�����ݣ������κ�ϵͳ���Բ����Լ��������ݡ�
  */
  int comptimemax;
  /**
  *  ���ѹ�������
  *  ��λ���룻
  *  ȱʡֵ��0��
  *  ���ĳ����ֵ����һ�����ύ����ʷ���ݿ����ֵ��ʱ����С�����ѹ�����������ֵ�ᱻ���ԣ�
  *  �������н��루suppress noise�������á�
  */
  int comptimemin;
  /**
  *  ����ƫ�
  *  ��λ����ǩ�㹤�̵�λ��
  *  ȱʡֵ��0.5��
  *  ���ĳ����ֵ����һ�����ύ�����ݴ洢������Server����ֵ��ƫ����ڸ�����ƫ�����ֵ�Ĺ��̵�λΪ׼���������ֵ����Ϊ������ֵ��Ӧ�ñ��ύ�����ݴ洢������Server��
  *  ��������ƫ��Ӧ��С�ڵ���ѹ��ƫ���һ�룻
  *  ��������[����ƫ��ٷֱȣ�The Percent of Exception Deviation��]���Ժ�����ͬ�������������̣�high
  *  limit - low limit���İٷֱȼ�[����ƫ��ٷֱȣ�The Percent of Exception
  *  Deviation��]���Ե�ֵ��
  *  �Ը����Ե��޸Ľ����¶�[����ƫ��ٷֱȣ�The Percent of Exception
  *  Deviation��]���޸ģ�ͬ������[����ƫ��ٷֱȣ�The Percent of Exception
  *  Deviation��]���޸�Ҳ���޸ĸ����ԣ��������ͬʱ���޸ģ�[����ƫ��ٷֱȣ�The Percent of Exception
  *  Deviation��]���и��ߵ�����Ȩ��
  */
  float excdev;
  /**
  *  ����ƫ��ٷֱȡ�
  *  ��λ���ٷֱȣ�
  *  �ο���[����ƫ��]��
  */
  float excdevpercent;
  /**
  *  �����������
  *  ��λ���룻
  *  ȱʡֵ��600��
  *  ���ĳ����ֵ����һ�����ύ�����ݴ洢������Server����ֵ��ʱ�������ڻ��������������������Ƿ�������������������ֵ��Ӧ�ñ���Ϊ������ֵ�Ӷ����ύ�����ݴ洢������Server��
  *  ���ݿ���������ǩ����ʱ�����п��ܳ���������ֵ����Ϊ�ӿڿ��ܳ�ʱ��ɼ��������ݣ������κ�ϵͳ���Բ����Լ��������ݣ�
  *  ���Ҫ�ر�������ˣ����ø�����Ϊ0���ɡ�
  */
  int exctimemax;
  /**
  *  �����������
  *  ��λ���룻
  *  ȱʡֵ��0��
  *  ���ĳ����ֵ����һ�����ύ�����ݴ洢������Server����ֵ��ʱ����С������������������Ƿ�������������������ֵ���ᱻ���ԣ�
  *  �������н��루suppress noise�������á�
  */
  int exctimemin;
  /**
  *  ��ǩ�����
  *  GOLDEN_CLASS���͵���ϣ���������չ��32�����͵���ϣ�
  *  ��������ǩ����̳���"����"���ͱ�ǩ�㡣
  *  ��ͬ���ı�ǩ����в�ͬ�����Լ���"�ɼ�"���ı�ǩ�����"�豸��ǩ"��"λ��"��"�Զ�������"��"�Զ��帡����"����չ���ԣ�"����"���ı�ǩ�����"��չ����"��"��������"����չ���ԡ�
  */
  unsigned int classof;
  /**
  *  ��ǩ���������һ�α��޸ĵ�ʱ�䡣
  */
  int changedate;
  /**
  *  ��ǩ���������һ�α��޸ĵ��û�����
  */
  char changer[GOLDEN_USER_SIZE];
  /**
  *  ��ǩ�㱻������ʱ�䡣
  */
  int createdate;
  /**
  *  ��ǩ�㴴���ߵ��û�����
  */
  char creator[GOLDEN_USER_SIZE];
  /**
  *  �����շ����ơ�
  *  Ĭ��ֵ���رգ�0
  *  ���������ͣ�1���Ƚ��գ��ַ���
  *  ����������գ�2��ֻ���գ�������
  *  ���������շ���3��ֻ���ͣ�������
  */
  golden_byte mirror;
  /**
  *  ʱ������ȡ�
  *  Ĭ��ֵ���룬0��
  *  �����趨��ǩ�����ʷֵ�ڴ洢�о�ȷ��"��"��0������"����"��1����
  *  ��ǩ��һ�������Ͳ������޸ĸ����ԡ�
  */
  golden_byte millisecond;
  /**
  *  �ɼ�����չ���Լ��洢��ַ������
  */
  unsigned int scanindex;
  /**
  *  �������չ���Լ��洢��ַ������
  */
  unsigned int calcindex;
  /**
  *  ��������չ���Լ��洢��ַ������
  */
  unsigned int alarmindex;
  /**
  *  ��ǩ��ȫ������ʽΪ��������.��ǩ�����ơ���
  */
  char table_dot_tag[GOLDEN_TAG_SIZE + GOLDEN_TAG_SIZE];
  /** 
  * ͳ�Ƽ��١�
  * Ĭ��ֵ���أ�0��
  * �����趨�Ƿ����ɱ�ǩ��ͳ����Ϣ���Ӷ�������ʷ����ͳ�ƹ��̡�
  */ 
  golden_byte summary; 
  /**
  *  ������ǩ�㱸���ֽڡ�
  */

  golden_uint16 named_type_id;
  golden_byte padding[GOLDEN_PACK_OF_POINT];
} GOLDEN_POINT;

/// �ɼ���ǩ����չ���Լ���
/**
 *  �ɼ���ǩ����չ���Լ���8�ֽڶ���������ռ��512�ֽڡ�
 */
typedef struct _GOLDEN_SCAN_POINT
{
  /**
  *  ȫ��Ψһ��ʶ��0��ʾ��Ч��
  */
  int id;
  /**
  *  ����Դ��
  *  ȱʡֵ���գ�NULL����
  *  ����ǩ��ͬĳЩ�ӿڻ�ĳЩģ���������
  *  ÿ������Դ�ַ���ֻ������26����ĸ����Сд���У������֣�0-9����ɣ��ֽڳ��Ȳ�Ҫ����255������Ĳ��ֻᱻ�ضϡ�
  */
  char source[GOLDEN_SOURCE_SIZE];
  /**
  *  �Ƿ�ɼ���
  *  ȱʡֵ��ON��1��
  *  �����Կ��ܻᱻĳЩ�ӿ��õ�����������Ա��رգ�OFF��0�����ӽӿڴ��������ݿ��ܲ��ᱻ���浽���ݿ⡣
  */
  golden_byte scan;
  /**
  *  �豸��ǩ��
  *  ȱʡֵ���գ�NULL����
  *  �ֽڳ��Ȳ�Ҫ����49������Ĳ��ֻᱻ�ضϡ�
  */
  char instrument[GOLDEN_INSTRUMENT_SIZE];
  /**
  *  ����������豸λַ��ȱʡֵȫ��Ϊ0��
  */
  int locations[GOLDEN_LOCATIONS_SIZE];
  /**
  *  �����������Զ���������ȱʡֵȫ��Ϊ0��
  */
  int userints[GOLDEN_USERINT_SIZE];
  /**
  *  �����������Զ��嵥���ȸ�������ȱʡֵȫ��Ϊ0��
  */
  float userreals[GOLDEN_USERREAL_SIZE];
  /**
  *  �ɼ���ǩ�㱸���ֽڡ�
  */
  golden_byte padding[GOLDEN_PACK_OF_SCAN];
} GOLDEN_SCAN_POINT;

/// �������չ���Լ���
/**
*  �������չ���Լ���8�ֽڶ���������ռ��2048�ֽڡ�
*/
typedef struct _GOLDEN_CALC_POINT
{
  /**
  *  ȫ��Ψһ��ʶ��0��ʾ��Ч��
  */
  int id;
  /**
  *  ʵʱ����ʽ��
  *  ȱʡֵ���գ�NULL����
  *  �ֽڳ��Ȳ�Ҫ����2047�����ȳ����ķ���ʽ�����ܾ�������⣬����һ�����󣬱������ķ���ʽ����ϵͳ����������ȫ���ء�
  */
  char equation[GOLDEN_EQUATION_SIZE];
  /**
  *  ���㴥�����ơ�ö��ֵ�μ� GOLDEN_TRIGGER��
  *  ����"����"����ǩ�������ã���������ʵʱ����ʽ����Ե��������ļ��㴥������"�¼�����"����"���ڴ���"��
  *  ����"���ڴ���"��"�¼�����"��Ϊ���Ⱦ��ж����������"�¼�����"�����㣬�򲻽���"���ڴ���"��
  */
  golden_byte trigger;
  /**
  *  ������ʱ����ο�, ö��ֵ�μ� GOLDEN_TIME_COPY
  *  0: ��ʾ���ü���ʱ����Ϊ������ʱ�����
  *  1: ��ʾ���������ǩ���е�����ʱ����Ϊ������ʱ�����
  *  2: ��ʾ���������ǩ���е�����ʱ����Ϊ������ʱ�����
  */
  golden_byte timecopy;
  /**
  *  ���ڡ����ڴ������ļ���㣬�趨��������ڣ���λ���롣
  */
  int period;
  // �����ǩ�㱸���ֽڡ�
  // golden_byte padding[GOLDEN_PACK_OF_CALC];
} GOLDEN_CALC_POINT;

/// �������չ���Լ���
/**
*  �������չ���Լ���8�ֽڶ���������ռ��512�ֽڡ�
*/
typedef struct _GOLDEN_MIN_CALC_POINT
{
  /**
  *  ȫ��Ψһ��ʶ��0��ʾ��Ч��
  */
  int id;
  /**
  *  ʵʱ����ʽ��
  *  ȱʡֵ���գ�NULL����
  *  �ֽڳ��Ȳ�Ҫ����480������ֽڳ��ȳ���480���뿼�ǵ���GOLDEN_CALC_POINT��GOLDEN_MAX_CALC_POINT
  */
  char equation[GOLDEN_MIN_EQUATION_SIZE];
  /**
  *  ���㴥�����ơ�ö��ֵ�μ� GOLDEN_TRIGGER��
  *  ����"����"����ǩ�������ã���������ʵʱ����ʽ����Ե��������ļ��㴥������"�¼�����"����"���ڴ���"��
  *  ����"���ڴ���"��"�¼�����"��Ϊ���Ⱦ��ж����������"�¼�����"�����㣬�򲻽���"���ڴ���"��
  */
  golden_byte trigger;
  /**
  *  ������ʱ����ο�, ö��ֵ�μ� GOLDEN_TIME_COPY
  *  0: ��ʾ���ü���ʱ����Ϊ������ʱ�����
  *  1: ��ʾ���������ǩ���е�����ʱ����Ϊ������ʱ�����
  *  2: ��ʾ���������ǩ���е�����ʱ����Ϊ������ʱ�����
  */
  golden_byte timecopy;
  /**
  *  ���ڡ����ڴ������ļ���㣬�趨��������ڣ���λ���롣
  */
  int period;
  /**
  *  �˷���ʽ�б�����Ƿ��Ƿ���ʽ
  */
  golden_byte is_equation;
  // �����ǩ�㱸���ֽڡ�
  golden_byte padding[GOLDEN_PACK_OF_MIN_CALC];
} GOLDEN_MIN_CALC_POINT;


/// �������չ���Լ���
/**
*  �������չ���Լ���8�ֽڶ���������ռ��6K�ֽڡ�
*/
typedef struct _GOLDEN_MAX_CALC_POINT
{
  /**
  *  ȫ��Ψһ��ʶ��0��ʾ��Ч��
  */
  int id;
  /**
  *  ʵʱ����ʽ��
  *  ȱʡֵ���գ�NULL����
  *  �ֽڳ��Ȳ�Ҫ����62 * 1024�����ȳ����ķ���ʽ�����ܾ�������⣬����һ�����󣬱������ķ���ʽ����ϵͳ����������ȫ���ء�
  */
  char equation[GOLDEN_MAX_EQUATION_SIZE];
  /**
  *  ���㴥�����ơ�ö��ֵ�μ� GOLDEN_TRIGGER��
  *  ����"����"����ǩ�������ã���������ʵʱ����ʽ����Ե��������ļ��㴥������"�¼�����"����"���ڴ���"��
  *  ����"���ڴ���"��"�¼�����"��Ϊ���Ⱦ��ж����������"�¼�����"�����㣬�򲻽���"���ڴ���"��
  */
  golden_byte trigger;
  /**
  *  ������ʱ����ο�, ö��ֵ�μ� GOLDEN_TIME_COPY
  *  0: ��ʾ���ü���ʱ����Ϊ������ʱ�����
  *  1: ��ʾ���������ǩ���е�����ʱ����Ϊ������ʱ�����
  *  2: ��ʾ���������ǩ���е�����ʱ����Ϊ������ʱ�����
  */
  golden_byte timecopy;
  /**
  *  ���ڡ����ڴ������ļ���㣬�趨��������ڣ���λ���롣
  */
  int period;
  // �����ǩ�㱸���ֽڡ�
  golden_byte padding[GOLDEN_PACK_OF_MAX_CALC];
} GOLDEN_MAX_CALC_POINT;

/// ��ǩ���ɱ�ṹ
typedef union _GOLDEN_TAG_FACTION
{
  unsigned int faction;
  struct
  {
    golden_byte type;
    golden_byte usems;
    golden_byte reserved1;
    golden_byte reserved2;
  } factions;
} GOLDEN_TAG_FACTION;

/**
*  ����ϵͳ����
*/
enum Golden_OS_Type
{
  GOLDEN_OS_WINDOWS,
  GOLDEN_OS_LINUX,
  GOLDEN_OS_INVALID = 50,
};

/**
*  �û�Ȩ��
*/
enum GOLDEN_PRIV_GROUP
{
  GOLDEN_RO,      /// ֻ��
  GOLDEN_DW,      /// ���ݼ�¼
  GOLDEN_TA,      /// ��ǩ������Ա
  GOLDEN_SA,      /// ���ݿ����Ա
};

/**
*  ��ǩ����ԭ��
*/
enum GOLDEN_TAG_CHANGE_REASON
{
  GOLDEN_TAG_CREATED = 1,  /// ��ǩ�㱻����
  GOLDEN_TAG_UPDATED,      /// ��ǩ�����Ա�����
  GOLDEN_TAG_REMOVED,      /// ��ǩ�㱻�������վ
  GOLDEN_TAG_RECOVERD,     /// ��ǩ�㱻�ָ�
  GOLDEN_TAG_PURGED,       /// ��ǩ�㱻���
  GOLDEN_TAB_UPDATED,      /// ��ǩ���������
  GOLDEN_TAB_REMOVED,      /// ��ǩ���ɾ��
};

/// ÿ����ʷ���ݴ浵�ļ����������99�������ļ�
#define GOLDEN_ARVEX_MAX          99

/// ��ʷ���ݴ浵�ļ�ͷ��ҳ
typedef struct _GOLDEN_HEADER_PAGE
{
  int db_ver;                             // �������ݿ�汾
  int data_ver;                           // ���ݸ�ʽ����汾
  int begin;                              // ������ʼʱ��
  int end;                                // ���ݽ���ʱ��
  long long real_size;                    // ʵ��д����ֽ��� ����ͳ��ʵ��ʹ����
  int create_time;                        // ����ʱ��
  int modify_time;                        // �޸�ʱ��
  int merge_time;                         // �ϴκϲ�ʱ��
  int arrange_time;                       // �ϴ�����ʱ��
  int reindex_time;                       // �ϴ��ؽ�����ʱ��
  int backup_time;                        // �ϴα���ʱ��
  long long rated_capacity;               // ����ʱ�������������
  long long capacity;                     // ��ǰ�������ļ��ڰ�����������ҳ����������ͷҳ��
  long long size;                         // ʵ��ʹ�������ѱ�ռ�õ�����ҳ����������ͷҳ��
  long long ex_capacity;                  // �����ļ�����
  golden_byte is_main;                    // �����ļ����Ǹ����ļ�
  golden_byte page_size;                  // ����ҳ���ֽڳߴ磬��λΪKB��
  golden_byte id_or_count;                // ���ļ��������Ÿ����ļ������������ļ��������������ID��
  golden_byte auto_merge;                 // �����Զ��ϲ�
  golden_byte auto_arrange;               // �����Զ�����
  golden_byte merged;                     // 1:�Ѻϲ���0:��δ�ϲ���ϲ����ֲ������µĸ����ļ���
  golden_byte arranged;                   // 1��������0����δ���������������ݷ��������
  golden_byte index_type;                 // �������ͣ�0 Ϊ�������1Ϊ��Ծ����Ĭ��Ϊ�����
  char file_name[GOLDEN_FILE_NAME_SIZE];  // ���������Լ����ļ�����
  golden_uint32 crc32;                    // �������ݵ�CRC32У���룬�ݲ����á�
  golden_byte index_in_mem;               // �����Ƿ���ص��ڴ���
  golden_error status;                    // �浵�ļ��ĵ�ǰ״̬
  char reserve_1[92];
} GOLDEN_HEADER_PAGE;       //��֤256�ֽ�

/// �û���Ϣ
typedef struct _GOLDEN_USER_INFO
{
  char user[GOLDEN_USER_SIZE];
  golden_int32 length;
  golden_int32 privilege;
  bool islocked;
  char reserve_1[15];
} GOLDEN_USER_INFO;         // 44 bytes

/// ϵͳ֧�ֵ����·������
#define GOLDEN_MAX_PATH                 2048

/// ϵͳ֧�ֵ��������������
#define GOLDEN_MAX_HOSTNAME_SIZE        1024

/// ���ӵ�GOLDEN���ݿ��������������Ϣ
typedef struct _GOLDEN_HOST_CONNECT_INFO
{
  golden_int32 ipaddr ;                                           /// ���ӵĿͻ���IP��ַ
  golden_uint16 port ;                                            /// ���Ӷ˿�
  golden_int32 job;                                               /// ����������������
  golden_int32 job_time;                                          /// ������������ʱ��
  golden_int32 connect_time;                                      /// �ͻ�������ʱ��
  char client[GOLDEN_MAX_HOSTNAME_SIZE];                          /// ���ӵĿͻ�����������
  char process[GOLDEN_PATH_SIZE+GOLDEN_FILE_NAME_SIZE];           /// ���ӵĿͻ��˳�����
  char user[GOLDEN_USER_SIZE];                                    /// ��¼���û�
  golden_int32 length;                                            /// ��¼�û������ȣ����ڼ��ܴ���
} GOLDEN_HOST_CONNECT_INFO, *PGOLDEN_HOST_CONNECT_INFO;

/// �����ǩ�㷽��ʽ����ͼ��ֵ����Ϣ
typedef struct _GOLDEN_FRAPH_DATA
{
	int id;														   /// ��ǩ��ID
	int parent_id;												   /// ��ǩ�㸸ID������ID����ʽ����������ID������
	char tag[GOLDEN_TAG_SIZE];									   /// ��ǩ������
	char error_msg[GOLDEN_DESC_SIZE];							   /// ��Ч��ǩ�������Ϣ
} GOLDEN_GRAPH;

enum GOLDEN_GRAPH_FLAG
{
  GOLDEN_GRAPH_BEGIN = -1,
  GOLDEN_GRAPH_ALL,       //�κ��й����ı�ǩ�Ĺ�ϵͼ
  GOLDEN_GRAPH_DIRECT,    //��ֱ�ӹ�ϵ�Ĺ�ϵͼ
  GOLDEN_GRAPH_END,
};

/// ��ʷ�浵�ļ�״̬
enum GOLDEN_ARCHIVE_STATE
{
  GOLDEN_INVALID_ARCHIVE, // 0:��Ч��
  GOLDEN_ACTIVED_ARCHIVE, // 1:���
  GOLDEN_NORMAL_ARCHIVE,  // 2:��ͨ��
  GOLDEN_READONLY_ARCHIVE // 3:ֻ��
};

enum GOLDEN_DB_PARAM_INDEX
{
	/// string parameter.
	GOLDEN_PARAM_STR_FIRST = 0x0,
	GOLDEN_PARAM_TABLE_FILE = GOLDEN_PARAM_STR_FIRST,   // ��ǩ����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_BASE_FILE,                             // ������ǩ���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_SCAN_FILE,                             // �ɼ���ǩ���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_CALC_FILE,                             // �����ǩ���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_SNAP_FILE,                             // ��ǩ������ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_LIC_FILE,                              // Э���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_HIS_FILE,                              // ��ʷ��Ϣ�ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_LOG_DIR,                               // ����������־�ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_USER_FILE,                             // �û�Ȩ����Ϣ�ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_SERVER_FILE,                           // �������������������̽������õĹ����ڴ��ļ����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_EQAUTION_FILE,                         // ����ʽ����������������̽������õĹ����ڴ��ļ����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_ARV_PAGES_FILE,                        // ��ʷ���ݻ����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_ARVEX_PAGES_FILE,                      // ����ʷ���ݻ����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_ARVEX_PAGES_BLOB_FILE,                 // ����ʷ����blob��str�����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_AUTH_FILE,                             // �������Ӷ���Ϣ�ļ�·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_RECYCLED_BASE_FILE,                    // �ɻ��ջ�����ǩ���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_RECYCLED_SCAN_FILE,                    // �ɻ��ղɼ���ǩ���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_RECYCLED_CALC_FILE,                    // �ɻ��ռ����ǩ���ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_AUTO_BACKUP_PATH,                      // �Զ�����Ŀ�ĵ�ȫ·���������ԡ�\����/���������ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_SERVER_SENDER_IP,                      // �����͵�ַ���ַ�����󳤶�Ϊ GOLDEN_MAX_HOSTNAME_SIZE
	GOLDEN_PARAM_BLACKLIST_FILE,                        // ���Ӻ������ļ�·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_DB_VERSION,                            // ���ݿ�汾
	GOLDEN_PARAM_LIC_USER,                              // ��Ȩ��λ
	GOLDEN_PARAM_LIC_TYPE,                              // ��Ȩ��ʽ
	GOLDEN_PARAM_INDEX_DIR,                             // �����ļ����Ŀ¼���ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_MIRROR_BUFFER_PATH,                    // ���񻺴��ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_MIRROR_EX_BUFFER_PATH,                 // ��д���񻺴��ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_EQAUTION_PATH_FILE,                    // ����ʽ���ȳ����涨����ʱ���б�����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_TAGS_FILE,                             // ��ǩ��ؼ������ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_RECYCLED_SNAP_FILE,                    // �ɻ��ձ�ǩ������¼��ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_SWAP_PAGE_FILE,						  // ��ʷ���ݽ���ҳ�ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_PAGE_ALLOCATOR_FILE,					  /* ��浵����ҳ�������ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
														  ��ϵͳ������2.1�����ݿ���ʹ�ã�3.0���ݿ���ȥ������Ϊ�˱�֤ϵͳѡ��������
														  ��2.1һ�£��˴�����ȥ��������java sdkͳһ����*/
	GOLDEN_PARAM_NAMED_TYPE_FILE,					      // �Զ�������������Ϣȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_STRBLOB_MIRROR_PATH,				      // BLOB/STRING�������ݻ����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_STRBLOB_MIRROR_EX_PATH,			      // ��дBLOB/STRING�������ݻ����ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_BUFFER_DIR,							  // ��ʱ���ݻ���·��
	GOLDEN_PARAM_POOL_CACHE_FLIE,					      // ���߳������ļ�ȫ·�����ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_POOL_DATA_FILE_DIR,				      // ���߳ػ����ļ�Ŀ¼���ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_ARCHIVE_FILE_PATH,				      // �Զ�����Ĵ浵�ļ�Ŀ¼���ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_LIC_VERSION_TYPE,                      // ��Ȩ�汾
  GOLDEN_PARAM_AUTO_MOVE_PATH,                        // �Զ��ƶ�Ŀ�ĵ�ȫ·���������ԡ�\����/���������ַ�����󳤶�Ϊ GOLDEN_MAX_PATH
	GOLDEN_PARAM_STR_LAST,

	// int parameter.
	GOLDEN_PARAM_INT_FIRST = 0x1000,
	GOLDEN_PARAM_LIC_TABLES_COUNT = GOLDEN_PARAM_INT_FIRST, // Э�����޶��ı�ǩ�������
	GOLDEN_PARAM_LIC_TAGS_COUNT,                        // Э�����޶������б�ǩ������
	GOLDEN_PARAM_LIC_SCAN_COUNT,                        // Э�����޶��Ĳɼ���ǩ������
	GOLDEN_PARAM_LIC_CALC_COUNT,                        // Э�����޶��ļ����ǩ������
	GOLDEN_PARAM_LIC_ARCHICVE_COUNT,                    // Э�����޶�����ʷ�浵�ļ�����
	GOLDEN_PARAM_SERVER_IPC_SIZE,                       // �������������������̽��н�����ʹ�õĹ����ڴ�ص��ֽڳߴ磨��λ��B��
	GOLDEN_PARAM_EQUATION_IPC_SIZE,                     // ����ʽ����������������̽��н�����ʹ�õĹ����ڴ�ص��ֽڳߴ磨��λ��B��
	GOLDEN_PARAM_HASH_TABLE_SIZE,                       // ��ǩ�������ϣ��ĳߴ�
	GOLDEN_PARAM_TAG_DELETE_TIMES/*obsolete*/,          // ������ɾ����ǩ��Ĵ���
	GOLDEN_PARAM_SERVER_PORT,                           // �����������������˿�
	GOLDEN_PARAM_SERVER_SENDER_PORT,                    // ����������Ͷ˿�
	GOLDEN_PARAM_SERVER_RECEIVER_PORT,                  // �����������ն˿�
	GOLDEN_PARAM_SERVER_MODE,                           // �����������ģʽ
	GOLDEN_PARAM_SERVER_CONNECTION_COUNT,               // Э�����޶�����������Ӳ������� 
	GOLDEN_PARAM_ARV_PAGES_NUMBER,                      // ��ʷ���ݻ����е�ҳ����
	GOLDEN_PARAM_ARVEX_PAGES_NUMBER,                    // ����ʷ���ݻ����е�ҳ����
	GOLDEN_PARAM_EXCEPTION_AT_SERVER,                   // �Ƿ��ɷ��������������ж�
	GOLDEN_PARAM_ARV_PAGE_RECYCLE_DELAY/*obsolete*/,    // ��ʷ���ݻ���ҳ������ʱ�����룩
	GOLDEN_PARAM_EX_ARCHIVE_SIZE,                       // ��ʷ���ݴ浵�ļ��ļ��Զ�������С����λ��MB��
	GOLDEN_PARAM_ARCHIVE_BATCH_SIZE,                    // ��ʷ�洢ֵ�ֶβ�ѯ����
	GOLDEN_PARAM_DATAFILE_PAGESIZE,                     // ϵͳ�����ļ�ҳ��С
	GOLDEN_PARAM_ARV_ASYNC_QUEUE_NORMAL_DOOR,           // ��ʷ���ݻ���������ٹ鵵������λ���ٷֱȣ�
	GOLDEN_PARAM_INDEX_ALWAYS_IN_MEMORY,                // ��פ�ڴ����ʷ����������С����λ��MB��
	GOLDEN_PARAM_DISK_MIN_REST_SIZE,                    // ��Ϳ��ô��̿ռ䣨��λ��MB��
	GOLDEN_PARAM_MIN_SIZE_OF_ARCHIVE,                   // ��ʷ�浵�ļ��͸����ļ�����С�ߴ磨��λ��MB��
	GOLDEN_PARAM_DELAY_OF_AUTO_MERGE_OR_ARRANGE,        // �Զ��ϲ�/������С�ӳ٣���λ��Сʱ��
	GOLDEN_PARAM_START_OF_AUTO_MERGE_OR_ARRANGE,        // �Զ��ϲ�/����ʼʱ�䣨��λ�����ӣ�
	GOLDEN_PARAM_STOP_OF_AUTO_MERGE_OR_ARRANGE,         // �Զ��ϲ�/����ֹͣʱ�䣨��λ�����ӣ�
	GOLDEN_PARAM_START_OF_AUTO_BACKUP,                  // �Զ����ݿ�ʼʱ�䣨��λ�����ӣ�
	GOLDEN_PARAM_STOP_OF_AUTO_BACKUP,                   // �Զ�����ֹͣʱ�䣨��λ�����ӣ�
	GOLDEN_PARAM_MAX_LATENCY_OF_SNAPSHOT,               // ���������ʱ��֮�����Сʱ�ڵ����ݽ�����գ���λ��Сʱ��
	GOLDEN_PARAM_PAGE_ALLOCATOR_RESERVE_SIZE,/*obsolete*/// �ҳ������Ԥ����С����λ��KB���� 0 ��ʾʹ�ò���ϵͳ��ͼ��С
	GOLDEN_PARAM_INCLUDE_SNAPSHOT_IN_QUERY,             // ����ȡ����ֵ��ͳ��ֵʱ�������Ƿ�Ӧ�ó����ڲ�ѯ�����
	GOLDEN_PARAM_LIC_BLOB_COUNT,                        // Э�����޶����ַ�����BLOB���ͱ�ǩ������
	GOLDEN_PARAM_MIRROR_BUFFER_SIZE,                    // �����ļ���С����λ��GB��
	GOLDEN_PARAM_BLOB_ARVEX_PAGES_NUMBER,               // blob��str����ʷ��Ĭ�ϻ���ҳ����
	GOLDEN_PARAM_MIRROR_EVENT_QUEUE_CAPACITY,           // ���񻺴��������
	GOLDEN_PARAM_NOTIFY_NOT_ENOUGH_SPACE,               // ��ʾ���̿ռ䲻�㣬һ�����ã�����ΪON����ͨ��API���ش�����룬����ֻ��¼��־
	GOLDEN_PARAM_ARCHIVE_FIXED_RANGE,                   // ��ʷ���ݴ浵�ļ��Ĺ̶�ʱ�䷶Χ��Ĭ��Ϊ0��ʾ��ʹ�ù̶�ʱ�䷶Χ����λ�����ӣ�
	GOLDEN_PARAM_ONE_CLINET_MAX_CONNECTION_COUNT,       // �����ͻ�������������������Ĭ��Ϊ0��ʾ������
	GOLDEN_PARAM_ARV_PAGES_CAPACITY,                    // ��ʷ���ݻ�����ռ�ֽڴ�С����λ���ֽ�
	GOLDEN_PARAM_ARVEX_PAGES_CAPACITY,                  // ��ʷ���ݲ�д������ռ�ֽڴ�С����λ���ֽ�
	GOLDEN_PARAM_BLOB_ARVEX_PAGES_CAPACITY,             // blob��string���ͱ�ǩ����ʷ���ݲ�д������ռ�ֽڴ�С����λ���ֽ�
	GOLDEN_PARAM_LOCKED_PAGES_MEM,                      // ָ����������ݿ��õ��ڴ��С����λ��MB
	GOLDEN_PARAM_LIC_RECYCLE_COUNT,                     // Э���л���վ������
	GOLDEN_PARAM_ARCHIVED_POLICY,                       // �������ݺͲ�д���ݵĹ鵵����
	GOLDEN_PARAM_NETWORK_ISOLATION_ACK_BYTE,            // �������װ��ACK�ֽ�


	GOLDEN_PARAM_ENABLE_LOGGER,                         // ������־�����0Ϊ������
	GOLDEN_PARAM_LOG_ENCODE,                            // ������־���ܣ�0Ϊ������
	GOLDEN_PARAM_LOGIN_TRY,                             // ���õ�¼ʧ�ܴ�����֤��0Ϊ������
	GOLDEN_PARAM_USER_LOG,                              // �����û���ϸ��־��0Ϊ������
	GOLDEN_PARAM_COVER_WRITE_LOG,                       // ������־����д���ܣ�0Ϊ������

	GOLDEN_PARAM_LIC_NAMED_TYPE_COUNT,				  // Э�����޶����Զ������ͱ�ǩ������
	GOLDEN_PARAM_MIRROR_RECEIVER_THREADPOOL_SIZE,		  // ��������߳�����
	GOLDEN_PARAM_SNAPSHOT_USE_ARCHIVE_INTERFACE,		  // ���ղ���ʷ���̹鵵��������ҳ
	GOLDEN_PARAM_NO_ARCDATA_WRITE_LOG,				  // �鵵�޶�Ӧ�浵�ļ�������ʱ��¼��־
	GOLDEN_PARAM_PUT_ARCHIVE_THREAD_NUM,				  // ����ʷ�鵵�߳���
	GOLDEN_PARAM_ARVEX_DATA_ARCHIVED_THRESHOLD,		  // ���β�д���ݹ鵵��ֵ
	GOLDEN_PARAM_SNAPSHOT_FLUSH_BUFFER_DELAY,			  // ���շ���Ĺ�����ˢ�µ����̵�����
	GOLDEN_PARAM_DATA_SPEED,							  // ��ѯʱʹ�ü���ͳ��
	GOLDEN_PARAM_USE_NEW_PLOT_ALGO,					  // �����µ������㷨
	GOLDEN_PARAM_QUERY_THREAD_POOL_SIZE,				  // ���߲�ѯ�̳߳����߳�����

#ifdef WIN32
	//Windows����ϵͳ����Ч
	//#ifdef _WIN64
	GOLDEN_PARAM_ARCHIVED_VALUES,						  // ʹ�ò�ѯ�̳߳ز�ѯ��ʷ����
	GOLDEN_PARAM_ARCHIVED_VALUES_COUNT,				  // ʹ�ò�ѯ�̳߳ز�ѯ��ʷ���ݵ�����
#else
	// Linux����ϵͳ����Ч
	GOLDEN_PARAM_ARCHIVED_VALUES_WITH_THREAD_POOL,          //!< ʹ�ò�ѯ�̳߳ز�ѯ��ʷ����
	GOLDEN_PARAM_ARCHIVED_VALUES_COUNT_WITH_THREAD_POOL,    //!< ʹ�ò�ѯ�̳߳ز�ѯ��ʷ���ݵ�����
	//#endif
#endif

	GOLDEN_PARAM_POOL_USE_FLAG,						  // �������߳�
	GOLDEN_PARAM_POOL_OUT_LOG_FLAG,					  // ������߳���־
	GOLDEN_PARAM_POOL_TIME_USE_POOL_FLAG,				  // ʹ�����߳ػ�������ֵ
	GOLDEN_PARAM_POOL_MAX_POINT_COUNT,				  // ���߳صı�ǩ������
	GOLDEN_PARAM_POOL_ONE_FILE_SAVE_POINT_COUNT,		  // ���߳�ÿ�������ļ��ı�ǩ������
	GOLDEN_PARAM_POOL_SAVE_MEMORY_SIZE,				  // ���߻����˳�ʱ��ʱ��������С
	GOLDEN_PARAM_POOL_MIN_TIME_UNIT_SECONDS,			  // ���߳ػ������ݵ�ǰʱ�䵥λ
	GOLDEN_PARAM_POOL_TIME_UNIT_VIEW_RATE,			  // ���߳ز�ѯ������Сʱ�䵥λ��ʾϵ��
	GOLDEN_PARAM_POOL_TIMER_INTERVAL_SECONDS,			  // ���߳ض�ʱ��ˢ������
	GOLDEN_PARAM_POOL_PERF_TIMER_INTERVAL_SECONDS,	  // ���߳����ܼ����ˢ������

	GOLDEN_PARAM_ARCHIVE_INIT_FILE_SIZE,				  // �浵�ļ���ʼ��С
	GOLDEN_PARAM_ARCHIVE_INCREASE_MODE,				  // �浵�ļ�����ģʽ
	GOLDEN_PARAM_ARCHIVE_INCREASE_SIZE,				  // �̶�ģʽ���ļ�������С
	GOLDEN_PARAM_ARCHIVE_INCREASE_PERCENT,			  // �ٷֱ�ģʽ�������ٷֱ�
	GOLDEN_PARAM_ALLOW_CONVERT_SKL_TO_RBT_INDEX,		  // ��Ծ����ת���������
	GOLDEN_PARAM_EARLY_DATA_TIME,						  // ������ʱ��
	GOLDEN_PARAM_EARLY_INDEX_TIME,					  // �Զ�ת������ʱ��
	GOLDEN_PARAM_ARRANGE_RBT_TIME,					  // ����浵�ļ�ʱ����������ʽ��ʱ����
	GOLDEN_PARAM_ENABLE_BIG_DATA,						  // ���浵�ļ�ȫ����ȡ���ڴ���
	GOLDEN_PARAM_AUTO_ARRANGE_PERCENT,				  // �Զ�����浵�ļ�ʱ��ʵ��ʹ����
	GOLDEN_PARAM_EARLY_ARRANGE_TIME,					  // �Զ�����浵�ļ���ʱ��
	GOLDEN_PARAM_MIN_AUTO_ARRANGE_ARCFILE_PERCENT,	  // �Զ�����浵�ļ�ʱ����Сʹ����
	GOLDEN_PARAM_ARRANGE_ARC_WITH_MEMORY,				  // ���ڴ�������浵�ļ�
	GOLDEN_PARAM_ARAANGE_ARC_MAX_MEM_PERCENT,			  // ����浵�ļ�����ڴ�ʹ����
	GOLDEN_PARAM_MAX_DISK_SPACE_PERCENT,				  // �������ʹ����
	GOLDEN_PARAM_USE_DISPATH,							  //windows �� linux �ѽ���,�Ƿ�����ת������
	GOLDEN_PARAM_USE_SMART_PARAM,						  //windows �� linux �ѽ���,�Ƿ�ʹ���Ƽ�����
	GOLDEN_PARAM_SUBSCRIBE_SNAPSHOT_COUNT,              // �����ӿ����¼����ĸ���
	GOLDEN_PARAM_SUBSCRIBE_QUEUE_SIZE,                  // �����¼����д�С
	GOLDEN_PARAM_SUBSCRIBE_TIMEOUT,                     // �����¼���ʱʱ��

	GOLDEN_PARAM_MIRROR_COMPRESS_ONOFF,				  // ������ѹ���Ƿ��
	GOLDEN_PARAM_MIRROR_COMPRESS_TYPE,				  // ������ѹ������
	GOLDEN_PARAM_MIRROR_COMPRESS_MIN,					  // ������ѹ����Сֵ
	GOLDEN_PARAM_ARCHIVE_ROLL_TIME,					  // �浵�ļ�����ʱ����
	GOLDEN_PARAM_HANDLE_TIME_OUT,						// ���ӳ�ʱ�Ͽ�����λ����
  GOLDEN_PARAM_ARRANGE_ARV_TIME,					  // �ƶ��浵�ļ�ʱ�����ƶ��浵��ʱ����
	GOLDEN_PARAM_INT_LAST,

	//exp int param
	GOLDEN_PARAM_EXP_INT_FIRST = 0x2000,
	GOLDEN_PARAM_MAX_BLOB_SIZE = GOLDEN_PARAM_EXP_INT_FIRST,   // blob��str�������������ݿ����������󳤶�
	GOLDEN_PARAM_EXP_INT_LAST,
};

//������ö��
enum GOLDEN_TABLE_ID
{
  GOLDEN_TABLE_BASE = 1,
  GOLDEN_TABLE_SCAN = 2,
  GOLDEN_TABLE_CALC = 4,
  GOLDEN_TABLE_ALARM = 8,
};
#define GOLDEN_TABLE_ID_CONTAIN_BASE(TABLEID) (TABLEID & GOLDEN_TABLE_BASE)
#define GOLDEN_TABLE_ID_CONTAIN_SCAN(TABLEID) (TABLEID & GOLDEN_TABLE_SCAN)
#define GOLDEN_TABLE_ID_CONTAIN_CALC(TABLEID) (TABLEID & GOLDEN_TABLE_CALC)
#define GOLDEN_TABLE_ID_CONTAIN_ALARM(TABLEID) (TABLEID & GOLDEN_TABLE_ALARM)
//���ֶ���Ϣ
#define GOLDEN_TAG_FIELD_NAME_LENGTH  20
#define GOLDEN_TAG_FIELD_TYPE_LENGTH    12
typedef struct TAG_GOLDEN_TAG_FIELD
{
  GOLDEN_TABLE_ID table_id;               //������
  golden_int16 column_index;                   //�ֶ����
  golden_int16 column_length;                 //�ֶγ���
  char column_name[GOLDEN_TAG_FIELD_NAME_LENGTH];  //�ֶ�����
  char column_type[GOLDEN_TAG_FIELD_TYPE_LENGTH];                    //�ֶ�����
} GOLDEN_TAG_FIELD;

enum GOLDEN_TAG_FIELD_INDEX
{
  GOLDEN_TAG_INDEX_BASE_FIRST = 0x0,
  GOLDEN_TAG_INDEX_TAG = GOLDEN_TAG_INDEX_BASE_FIRST, // tag
  GOLDEN_TAG_INDEX_ID,                                // id
  GOLDEN_TAG_INDEX_TYPE,                              // type
  GOLDEN_TAG_INDEX_TABLE,                             // table
  GOLDEN_TAG_INDEX_DESC,                              // desc
  GOLDEN_TAG_INDEX_UNIT,                              // unit
  GOLDEN_TAG_INDEX_ARCHIVE,                           // archive
  GOLDEN_TAG_INDEX_DIGITS,                            // digits
  GOLDEN_TAG_INDEX_SHUTDOWN,                          // shutdown
  GOLDEN_TAG_INDEX_LOWLIMIT,                          // lowlimit
  GOLDEN_TAG_INDEX_HIGHLIMIT,                         // highlimit
  GOLDEN_TAG_INDEX_STEP,                              // step
  GOLDEN_TAG_INDEX_TYPICAL,                           // typical
  GOLDEN_TAG_INDEX_COMPRESS,                          // compress
  GOLDEN_TAG_INDEX_COMPDEV,                           // compdev
  GOLDEN_TAG_INDEX_COMPDEVPERCENT,                    // compdevpercent
  GOLDEN_TAG_INDEX_COMPTIMEMAX,                       // comptimemax
  GOLDEN_TAG_INDEX_COMPTIMEMIN,                       // comptimemin
  GOLDEN_TAG_INDEX_EXCDEV,                            // excdev
  GOLDEN_TAG_INDEX_EXCDEVPERCENT,                     // excdevpercent
  GOLDEN_TAG_INDEX_EXCTIMEMAX,                        // exctimemax
  GOLDEN_TAG_INDEX_EXCTIMEMIN,                        // exctimemin
  GOLDEN_TAG_INDEX_CLASSOF,                           // classof
  GOLDEN_TAG_INDEX_CHANGEDATE,                        // changedate
  GOLDEN_TAG_INDEX_CHANGER,                           // changer
  GOLDEN_TAG_INDEX_CREATEDATE,                        // createdate
  GOLDEN_TAG_INDEX_CREATOR,                           // creator
  GOLDEN_TAG_INDEX_MIRROR,                            // mirror
  GOLDEN_TAG_INDEX_MS,                                // millisecond
  GOLDEN_TAG_INDEX_FULLNAME,                          // table_dot_tag
  GOLDEN_TAG_INDEX_SUMMARY,                           // summary
  GOLDEN_TAG_INDEX_BASE_LAST, 
  
  GOLDEN_TAG_INDEX_SCAN_FIRST = 0x1000, 
  GOLDEN_TAG_INDEX_SOURCE = GOLDEN_TAG_INDEX_SCAN_FIRST, // source
  GOLDEN_TAG_INDEX_SCAN,                              // scan
  GOLDEN_TAG_INDEX_INSTRUMENT,                        // instrument
  GOLDEN_TAG_INDEX_LOCATION1,                         // locations[0]
  GOLDEN_TAG_INDEX_LOCATION2,                         // locations[2]
  GOLDEN_TAG_INDEX_LOCATION3,                         // locations[3]
  GOLDEN_TAG_INDEX_LOCATION4,                         // locations[4]
  GOLDEN_TAG_INDEX_LOCATION5,                         // locations[5]
  GOLDEN_TAG_INDEX_USERINT1,                          // userints[0]
  GOLDEN_TAG_INDEX_USERINT2,                          // userints[1]
  GOLDEN_TAG_INDEX_USERREAL1,                         // userreals[0]
  GOLDEN_TAG_INDEX_USERREAL2,                         // userreals[1]
  GOLDEN_TAG_INDEX_SCAN_LAST, 

  GOLDEN_TAG_INDEX_CALC_FIRST = 0x2000,
  GOLDEN_TAG_INDEX_EQUATION = GOLDEN_TAG_INDEX_CALC_FIRST, // equation
  GOLDEN_TAG_INDEX_TRIGGER,                           // trigger
  GOLDEN_TAG_INDEX_TIMECOPY,                          // timecopy
  GOLDEN_TAG_INDEX_PERIOD,                            // period
  GOLDEN_TAG_INDEX_CALC_LAST, 

  GOLDEN_TAG_INDEX_SNAPSHOT_FIRST = 0x3000, 
  GOLDEN_TAG_INDEX_TIMESTAMP = GOLDEN_TAG_INDEX_SNAPSHOT_FIRST, // snapshot stamp (ms)
  GOLDEN_TAG_INDEX_VALUE,                             // snapshot value
  GOLDEN_TAG_INDEX_QUALITY,                           // snapshot quality
  GOLDEN_TAG_INDEX_SNAPSHOT_LAST, 
}; 

enum GOLDEN_TAG_SORT_FLAG
{
  GOLDEN_SORT_FLAG_DESCEND = 0x0001, 
  GOLDEN_SORT_FLAG_CASE_SENSITIVE = 0x0002, 
  GOLDEN_SORT_FLAG_RECYCLED = 0x0004, 
}; 

/// ���ܼ������ID
enum GOLDEN_PERF_TAG_ID
{
  PFT_CPU_USAGE_OF_LOGGER,            // ��־����CPUʹ��
  PFT_MEM_BYTES_OF_LOGGER,            // ��־�����ڴ�
  PFT_VMEM_BYTES_OF_LOGGER,           // ��־���������ڴ�
  PFT_READ_BYTES_OF_LOGGER,           // ��־���� I/O ��ȡ�ֽ�
  PFT_WRITE_BYTES_OF_LOGGER,          // ��־���� I/O д���ֽ�
  PFT_CPU_USAGE_OF_HISTORIAN,         // ��ʷ���ݷ���CPUʹ��
  PFT_MEM_BYTES_OF_HISTORIAN,         // ��ʷ���ݷ����ڴ�
  PFT_VMEM_BYTES_OF_HISTORIAN,        // ��ʷ���ݷ��������ڴ�
  PFT_READ_BYTES_OF_HISTORIAN,        // ��ʷ���ݷ��� I/O ��ȡ�ֽ�
  PFT_WRITE_BYTES_OF_HISTORIAN,       // ��ʷ���ݷ��� I/O д���ֽ�
  PFT_CPU_USAGE_OF_SNAPSHOT,          // �������ݷ���CPUʹ��
  PFT_MEM_BYTES_OF_SNAPSHOT,          // �������ݷ����ڴ�
  PFT_VMEM_BYTES_OF_SNAPSHOT,         // �������ݷ��������ڴ�
  PFT_READ_BYTES_OF_SNAPSHOT,         // �������ݷ��� I/O ��ȡ�ֽ�
  PFT_WRITE_BYTES_OF_SNAPSHOT,        // �������ݷ��� I/O д���ֽ�
  PFT_CPU_USAGE_OF_EQUATION,          // ʵʱ����ʽ����CPUʹ��
  PFT_MEM_BYTES_OF_EQUATION,          // ʵʱ����ʽ�����ڴ�
  PFT_VMEM_BYTES_OF_EQUATION,         // ʵʱ����ʽ���������ڴ�
  PFT_READ_BYTES_OF_EQUATION,         // ʵʱ����ʽ���� I/O ��ȡ�ֽ�
  PFT_WRITE_BYTES_OF_EQUATION,        // ʵʱ����ʽ���� I/O д���ֽ�
  PFT_CPU_USAGE_OF_BASE,              // ��ǩ����Ϣ����CPUʹ��
  PFT_MEM_BYTES_OF_BASE,              // ��ǩ����Ϣ�����ڴ�
  PFT_VMEM_BYTES_OF_BASE,             // ��ǩ����Ϣ���������ڴ�
  PFT_READ_BYTES_OF_BASE,             // ��ǩ����Ϣ���� I/O ��ȡ�ֽ�
  PFT_WRITE_BYTES_OF_BASE,            // ��ǩ����Ϣ���� I/O д���ֽ�
  PFT_CPU_USAGE_OF_SERVER,            // �������CPUʹ��
  PFT_MEM_BYTES_OF_SERVER,            // ��������ڴ�
  PFT_VMEM_BYTES_OF_SERVER,           // ������������ڴ�
  PFT_READ_BYTES_OF_SERVER,           // ������� I/O ��ȡ�ֽ�
  PFT_WRITE_BYTES_OF_SERVER,          // ������� I/O д���ֽ�
  PFT_ARV_ASYNC_QUEUE,                // ��ʷ���ݶ��е�ַ
  PFT_ARV_ASYNC_QUEUE_USAGE,          // ��ʷ���ݶ���ʹ����
  PFT_ARVEX_ASYNC_QUEUE,              // ����ʷ���ݶ��е�ַ
  PFT_ARVEX_ASYNC_QUEUE_USAGE,        // ����ʷ���ݶ���ʹ����
  PFT_EVENTS_INPUT_RATE,              // ��ͨ�¼�����ٶȣ�KB/�룩
  PFT_EVENTS_OUTPUT_RATE,             // ��ͨ�¼��鵵�ٶȣ�KB/�룩
  PFT_FILL_IN_INPUT_RATE,             // ����ʷ�¼�����ٶȣ�KB/�룩
  PFT_FILL_IN_OUTPUT_RATE,            // ����ʷ�¼��鵵�ٶȣ�KB/�룩
  PFT_ARV_CACHE_USAGE,                // ��ʷ���ݻ���ʹ����
  PFT_ARVEX_CACHE_USAGE,              // ����ʷ���ݻ���ʹ����
  PFT_MIRROR_SNAPSHOTS_QUEUE,         // �������ݵľ�����е�ַ
  PFT_MIRROR_SNAPSHOTS_QUEUE_USAGE,   // �������ݵľ������ʹ����
  PFT_ARVEX_BLOB_ASYNC_QUEUE,         // str��blob����ʷ���ݶ��е�ַ
  PFT_ARVEX_BLOB_ASYNC_QUEUE_USAGE,   // str��blob����ʷ���ݶ���ʹ����
  PFT_ARVEX_BLOB_CACHE_USAGE,         // str��blob����ʷ���ݻ���ʹ����
  PFT_MIRROR_BUFFER_SIZE,             // �������ݵľ��񻺴��ļ�
  PFT_CLUTTER_POOL_USAGE,             // ��Ϣ������������
  PFT_MAX_BLOCK_IN_CLUTTER_POOL,      // ��Ϣ�����ص������ö��
  PFT_ARV_ARCHIVED_TIME,              // ��ʷ���ݹ鵵��ʱ
  PFT_ARVEX_ARCHIVED_TIME,            // ����ʷ���ݹ鵵��ʱ
  PFT_ARVEX_BLOB_ARCHIVED_TIME,       // str��blob����ʷ���ݹ鵵��ʱ
  PFT_ARV_ARCHIVED_PAGE_COUNT,        // ��ʷ���ݹ鵵������ҳ����
  PFT_ARVEX_ARCHIVED_PAGE_COUNT,      // ����ʷ���ݹ鵵������ҳ����
  PFT_ARVEX_BLOB_ARCHIVED_PAGE_COUNT, // str��blob����ʷ���ݹ鵵������ҳ����
  PFT_MIRROR_ARV_VALUES_QUEUE,        // ��д��ʷ���ݵľ�����е�ַ
  PFT_MIRROR_ARV_VALUES_QUEUE_USAGE,  // ��д��ʷ���ݵľ������ʹ����
  PFT_MIRROR_ARV_BUFFER_SIZE,         // ��д��ʷ���ݵľ��񻺴��ļ�

  PFT_ARV_WRITE_COUNT,                //��ʷ���ݹ鵵д���̴���
  PFT_ARV_READ_COUNT,                 //��ʷ���ݹ鵵�����̴���
  PFT_ARV_WRITE_TIME,                 //��ʷ���ݹ鵵д����ʱ��
  PFT_ARV_READ_TIME,                  //��ʷ���ݹ鵵������ʱ��
  PFT_ARV_INDEX_WRITE_COUNT,          //��ʷ���ݹ鵵д��������
  PFT_ARV_INDEX_READ_COUNT,           //��ʷ���ݹ鵵����������
  PFT_ARV_INDEX_WRITE_TIME,           //��ʷ���ݹ鵵д����ʱ��
  PFT_ARV_INDEX_READ_TIME,            //��ʷ���ݹ鵵������ʱ��
  PFT_ARV_ARC_LIST_LOCK_TIME,         //��ʷ���ݹ鵵�б���ʱ��
  PFT_ARV_ARC_LOCK_TIME,              //��ʷ���ݹ鵵�ļ���ʱ��
  PFT_ARV_INDEX_LOCK_TIME,            //��ʷ���ݹ鵵������ʱ��
  PFT_ARV_TOTAL_LOCK_TIME,            //��ʷ���ݹ鵵����ʱ��
  PFT_ARV_WRITE_SIZE,                 //��ʷ���ݹ鵵д����������
  PFT_ARV_READ_SIZE,                  //��ʷ���ݹ鵵������������
  PFT_ARV_WRITE_REAL_SIZE,            //��ʷ���ݹ鵵д������Ч������
  PFT_ARV_READ_REAL_SIZE,             //��ʷ���ݹ鵵��������Ч������
  PFT_ARVEX_WRITE_COUNT,              //����ʷ���ݹ鵵д���̴���
  PFT_ARVEX_READ_COUNT,               //����ʷ���ݹ鵵�����̴���
  PFT_ARVEX_WRITE_TIME,               //����ʷ���ݹ鵵д����ʱ��
  PFT_ARVEX_READ_TIME,                //����ʷ���ݹ鵵������ʱ��
  PFT_ARVEX_INDEX_WRITE_COUNT,        //����ʷ���ݹ鵵д��������
  PFT_ARVEX_INDEX_READ_COUNT,         //����ʷ���ݹ鵵����������
  PFT_ARVEX_INDEX_WRITE_TIME,         //����ʷ���ݹ鵵д����ʱ��
  PFT_ARVEX_INDEX_READ_TIME,          //����ʷ���ݹ鵵������ʱ��
  PFT_ARVEX_ARC_LIST_LOCK_TIME,       //����ʷ���ݹ鵵�б���ʱ��
  PFT_ARVEX_ARC_LOCK_TIME,            //����ʷ���ݹ鵵�ļ���ʱ��
  PFT_ARVEX_INDEX_LOCK_TIME,          //����ʷ���ݹ鵵������ʱ��
  PFT_ARVEX_TOTAL_LOCK_TIME,          //����ʷ���ݹ鵵����ʱ��
  PFT_ARVEX_WRITE_SIZE,               //����ʷ���ݹ鵵д����������
  PFT_ARVEX_READ_SIZE,                //����ʷ���ݹ鵵������������
  PFT_ARVEX_WRITE_REAL_SIZE,          //����ʷ���ݹ鵵д������Ч������
  PFT_ARVEX_READ_REAL_SIZE,           //����ʷ���ݹ鵵��������Ч������

  PFT_PLOT_POOL_POINT_COUNT,          //���߻����ǩ������
  PFT_PLOT_POOL_WEIGHTED_POINT_COUNT, //���߻���Ȩ�ص�����
  PFT_PLOT_POOL_TOTAL_MEM_SIZE,       //���߻������ڴ���
  PFT_PLOT_POOL_CACHED_HIT_PERCENT,   //���߻���������
  
  PFT_OS_CPU_USAGE,                   // ���ݿ����ڲ���ϵͳ��CPUʹ����
  PFT_OS_MEM_SIZE,                    // ���ݿ����ڲ���ϵͳ�������ڴ��С����λMB
  PFT_OS_MEM_USAGE,                   // ���ݿ����ڲ���ϵͳ�������ڴ�ʹ���� 

  PFT_QUERY_POOL_WAIT_TASKS_SIZE,          // ��ѯ�̳߳��еȴ�ִ�е�������

  PFT_MIRROR_EN_QUEUE,                // ��������ÿ�������(�ֽ�)
  PFT_MIRROT_OUT_QUEUE,               // ��������ÿ�������(�ֽ�)
  PFT_MIRROR_SEND_CPRS,               // ��������ÿ��ѹ����(�ֽ�)
  PFT_MIRROR_RECV_CPRS,               // ��������ÿ�������(�ֽ�)
  PFT_MIRROR_RECV_UNCPRS,             // ��������ÿ���ѹ����(�ֽ�) 
  PFT_MIRROR_CPRS_SPAN,               // ��������ÿ��ѹ����ʱ(����)
  PFT_MIRROR_COMPRESS_RATE,			  // 1���ھ����ѹ����

  PFT_END,                            // ��Ϣ����
};

/// ���ܼ��������Ϣ
typedef struct  _GOLDEN_PERF_TAG_INFO
{
  int perf_id;                        /// ���ܼ������ID �ο�GOLDEN_PERF_TAG_ID
  char tag_name[GOLDEN_TAG_SIZE];     /// ���ܼ����������
  char desc[GOLDEN_DESC_SIZE];        /// ���ܼ����������
  char unit[GOLDEN_UNIT_SIZE];        /// ���ܼ�������ֵ�ĵ�λ
  int type;                           /// ���ܼ��������ֵ����
} GOLDEN_PERF_TAG_INFO;

/// ����Զ������͵��ֶζ���
typedef struct _GOLDEN_DATA_TYPE_FIELD
{
  char         name[GOLDEN_TYPE_NAME_SIZE]; /// �Զ������͵��ֶε����ƣ���Ҫ����GOLDEN_TYPE_NAME_SIZE���ֽ�
  golden_int32 type;                        /// �ֶε�����,ֻ֧��GOLDEN_TYPE������ͣ���֧��struct��union��������͡�
  golden_int32 length;                      /// �ֶ����͵ĳ���,string,blob�����͵ľ���ĳ��ȣ��������ͱ���ĳ���(�������Ϳ��Ժ���)����λ���ֽڡ�
  char         desc[GOLDEN_DESC_SIZE];
} GOLDEN_DATA_TYPE_FIELD, *PGOLDEN_DATA_TYPE_FIELD;

enum GOLDEN_TAG_LOAD_MEMORY_FLAG
{
  GOLDEN_LOAD_EMPTY_POINT   = 0x0,                                    //ʲôҲ������

  GOLDEN_LOAD_TABLE_DOT_TAG = 0x1,                                    //���ȫ����
  GOLDEN_LOAD_DESC          = 0x2,                                    //����
  GOLDEN_LOAD_UNIT          = 0x4,                                    //��λ
  GOLDEN_LOAD_CHANGER       = 0x8,                                    //�޸���
  GOLDEN_LOAD_CREATOR       = 0x10,                                   //������
  GOLDEN_LOAD_LOWLIMIT      = 0x20,                                   //����
  GOLDEN_LOAD_HIGHLIMIT     = 0x40,                                   //����
  GOLDEN_LOAD_TYPICAL       = 0x80,                                   //����ֵ
  GOLDEN_LOAD_CHANGEDATE    = 0x100,                                  //�޸�����
  GOLDEN_LOAD_CREATEDATE    = 0x200,                                  //��������
  GOLDEN_LOAD_DIGITS        = 0x400,                                  //��ֵλ��

  GOLDEN_LOAD_COMPDEVPERCENT= 0x800,                                  //ѹ��ƫ��ٷֱ�
  GOLDEN_LOAD_EXCDEVPERCENT = 0x1000,                                 //����ƫ��ٷֱ�

  GOLDEN_LOAD_SOURCE        = 0x10000,                                //����Դ
  GOLDEN_LOAD_SCAN          = 0x20000,                                //�Ƿ�ɼ�
  GOLDEN_LOAD_INSTRUMENT    = 0x40000,                                //�豸��ǩ
  GOLDEN_LOAD_LOCATION1     = 0x80000,                                //�豸λַ1
  GOLDEN_LOAD_LOCATION2     = 0x100000,                               //�豸λַ2
  GOLDEN_LOAD_LOCATION3     = 0x200000,                               //�豸λַ3
  GOLDEN_LOAD_LOCATION4     = 0x400000,                               //�豸λַ4
  GOLDEN_LOAD_LOCATION5     = 0x800000,                               //�豸λַ5
  GOLDEN_LOAD_USERINT1      = 0x1000000,                              //�Զ�������1
  GOLDEN_LOAD_USERINT2      = 0x2000000,                              //�Զ�������2
  GOLDEN_LOAD_USERREAL1     = 0x4000000,                              //�Զ��帡����1
  GOLDEN_LOAD_USERREAL2     = 0x8000000,                              //�Զ��帡����2

  GOLDEN_LOAD_BASE_POINT    = GOLDEN_LOAD_TABLE_DOT_TAG | GOLDEN_LOAD_DESC | GOLDEN_LOAD_UNIT | GOLDEN_LOAD_CHANGER | GOLDEN_LOAD_CREATOR | GOLDEN_LOAD_LOWLIMIT | GOLDEN_LOAD_HIGHLIMIT | GOLDEN_LOAD_TYPICAL | GOLDEN_LOAD_CHANGEDATE | GOLDEN_LOAD_CREATEDATE | GOLDEN_LOAD_DIGITS | GOLDEN_LOAD_COMPDEVPERCENT | GOLDEN_LOAD_EXCDEVPERCENT,                          //base ���Ժϼ�
  GOLDEN_LOAD_SCAN_POINT    = GOLDEN_LOAD_SOURCE | GOLDEN_LOAD_SCAN | GOLDEN_LOAD_INSTRUMENT | GOLDEN_LOAD_LOCATION1 | GOLDEN_LOAD_LOCATION2 | GOLDEN_LOAD_LOCATION3 | GOLDEN_LOAD_LOCATION4 | GOLDEN_LOAD_LOCATION5 | GOLDEN_LOAD_USERINT1 | GOLDEN_LOAD_USERINT2 | GOLDEN_LOAD_USERREAL1 | GOLDEN_LOAD_USERREAL2, //scan ���Ժϼ�
  GOLDEN_LOAD_ALL_POINT     = GOLDEN_LOAD_BASE_POINT | GOLDEN_LOAD_SCAN_POINT,  //�������Ժϼ�
};

#define GOLDEN_GET_FROM_FLAG(FLAG, BIT) (((FLAG) & (BIT)) ? 1 : 0)
#define GOLDEN_SET_FROM_FLAG(FLAG, BIT, VALUE) {if (VALUE) (FLAG) |= (BIT); else (FLAG) &= (~(BIT));}

#define GOLDEN_HAS_EMPTY_FROM_FLAG(FLAG) (((FLAG) & (GOLDEN_LOAD_EMPTY_POINT)) ? 1 : 0)
#define GOLDEN_HAS_BASE_FROM_FLAG(FLAG) (((FLAG) & (GOLDEN_LOAD_BASE_POINT)) ? 1 : 0)
#define GOLDEN_HAS_SCAN_FROM_FLAG(FLAG) (((FLAG) & (GOLDEN_LOAD_SCAN_POINT)) ? 1 : 0)
#define GOLDEN_HAS_ALL_FROM_FLAG(FLAG) (((FLAG) & (GOLDEN_LOAD_ALL_POINT)) ? 1 : 0)

enum GOLDEN_ARCHIVED_POLICY
{
  GOLDEN_ARCHIVED_SNAPSHOT_FIRST,           //�����������ȹ鵵
  GOLDEN_ARCHIVED_ARCHIVEX_FIRST,           //��д�������ȹ鵵
  GOLDEN_ARCHIVED_AUTO,                     //�Զ��жϿ������ݺͲ�д���ݵ����ȼ�
  GOLDEN_ARCHIVED_PAUSE,                    //��ͣ�鵵
};

enum API_CATEGORY
{
  API_SERVER,
  API_BASE,
  API_SNAPSHOT,
  API_HISTORIAN,
  API_ARCHIVE,
  API_EQUATION,
  API_LOGGER,
  API_PERF,
  API_DISPATCH,
  API_MEMORYDB,
};

typedef struct _GOLDEN_CONNECT_EVENT
{
  golden_int32 msg_id;                      //���õķ���ID
  golden_int32 begin_s;                     //���õĿ�ʼʱ��
  golden_int16 begin_ms;                    //���õĿ�ʼʱ��ĺ���
  golden_int16 api_category;                //���õ�API���
  golden_uint32 client_addr;                //�ͻ��˵�IP��ַ
  golden_int32 client_process_id;           //�ͻ��˵Ľ���ID
  golden_int32 client_thread_id;            //�ͻ��˵��߳�ID
  golden_int32 server_thread_id;            //����˵��߳�ID
  golden_error ret_val;                     //���õķ�������ֵ
  golden_float32 elapsed;                   //���õķ���˺�ʱ ��λ����
  golden_int32 pre_count;                   //����ʱ�����count
  golden_int32 post_count;                  //����ʱ������count

  golden_uint32 write_count;                //��ʷ�����ѯ��д���̴���
  golden_uint32 read_count;                 //��ʷ�����ѯ�Ķ����̴���
  golden_float32 write_time;                //��ʷ�����ѯ��д����ʱ��
  golden_float32 read_time;                 //��ʷ�����ѯ�Ķ�����ʱ��
  golden_uint32 index_write_count;          //��ʷ�����ѯ��д��������
  golden_uint32 index_read_count;           //��ʷ�����ѯ�Ķ���������
  golden_float32 index_write_time;          //��ʷ�����ѯ��д����ʱ��
  golden_float32 index_read_time;           //��ʷ�����ѯ�Ķ�����ʱ��
  golden_float32 arc_list_lock_time;        //��ʷ�����ѯ���ļ��б���ʱ��
  golden_float32 arc_lock_time;             //��ʷ�����ѯ�Ĵ浵�ļ���ʱ��
  golden_float32 index_lock_time;           //��ʷ�����ѯ��������ʱ��
  golden_float32 total_lock_time;           //��ʷ�����ѯ��������ʱ��
  golden_float32 write_size;                //��ʷ�����ѯ��д������������λKB
  golden_float32 read_size;                 //��ʷ�����ѯ�Ķ�ȡ����������λKB
  golden_float32 write_real_size;           //��ʷ�����ѯ��д����Ч����������λKB
  golden_float32 read_real_size;            //��ʷ�����ѯ�Ķ�ȡ��Ч����������λKB

  char reserve_1[20];                       //�����ֽ�
}GOLDEN_CONNECT_EVENT;    //128�ֽ�

typedef struct _GOLDEN_ARCHIVE_PERF_DATA
{
  golden_uint32 write_count;                //��ʷ�����ѯ��д���̴���
  golden_uint32 read_count;                 //��ʷ�����ѯ�Ķ����̴���
  golden_float32 write_time;                //��ʷ�����ѯ��д����ʱ��
  golden_float32 read_time;                 //��ʷ�����ѯ�Ķ�����ʱ��
  golden_uint32 index_write_count;          //��ʷ�����ѯ��д��������
  golden_uint32 index_read_count;           //��ʷ�����ѯ�Ķ���������
  golden_float32 index_write_time;          //��ʷ�����ѯ��д����ʱ��
  golden_float32 index_read_time;           //��ʷ�����ѯ�Ķ�����ʱ��
  golden_float32 arc_list_lock_time;        //��ʷ�����ѯ���ļ��б���ʱ��
  golden_float32 arc_lock_time;             //��ʷ�����ѯ�Ĵ浵�ļ���ʱ��
  golden_float32 index_lock_time;           //��ʷ�����ѯ��������ʱ��
  golden_float32 total_lock_time;           //��ʷ�����ѯ��������ʱ��
  golden_float32 write_size;                //��ʷ�����ѯ��д������������λKB
  golden_float32 read_size;                 //��ʷ�����ѯ�Ķ�ȡ����������λKB
  golden_float32 write_real_size;           //��ʷ�����ѯ��д����Ч����������λKB
  golden_float32 read_real_size;            //��ʷ�����ѯ�Ķ�ȡ��Ч����������λKB
}GOLDEN_ARCHIVE_PERF_DATA;      //64�ֽ�

/**
* ������gob_tags_change_event
* ���ܣ���ǩ�����Ը���֪ͨ���Ļص��ӿ�
* ������
*        [count]     ���ͣ����룬��ǩ�������ids �ĳ��ȣ�
*        [ids]       �������飬���룬��ǩ�㱻���������Է������ĵı�ʶ�б�
*        [what]      ���ͣ��ο�ö�� GOLDEN_TAG_CHANGE_REASON, 
*                    ��ʾ��������Դ���͡�
*/
typedef 
golden_error 
(*gob_tags_change_event)(
                   golden_int32 count, 
                   const golden_int32 *ids,
                   golden_int32 what
                   );

typedef gob_tags_change_event gob_tags_change;

/**
* ������gob_tags_change_event_ex
* ���ܣ���ǩ�����Ը���֪ͨ���Ļص��ӿ�
* ������
*        [event_type]   �޷������Σ����룬֪ͨ���ͣ��ο�ö�� GOLDEN_EVENT_TYPE
*        [handle]       ���ͣ����룬����֪ͨ�ľ��
*        [param]        voidָ�룬���룬�û�����gob_subscribe_tags_exʱparam����
*        [count]        ���ͣ����룬��ǩ�������ids�ĳ���
*        [ids]          �������飬���룬��ǩ�㱻���������Է������ĵı�ʶ�б�
*        [what]         ���ͣ��ο�ö�� GOLDEN_TAG_CHANGE_REASON,
*                       ��ʾ��������Դ���͡�
*/
typedef
golden_error
(*gob_tags_change_event_ex)(
golden_uint32 event_type,
golden_int32 handle,
void* param,
                   golden_int32 count, 
                   const golden_int32 *ids,
                   golden_int32 what
                   );

/**
* ������gos_snaps_event
* ���ܣ���ǩ����ոı�֪ͨ���Ļص��ӿ�
* ������
*        [count]     ���ͣ����룬
*                    ��ʾ ids��datetimes��ms��values��states��qualities��errors�ĳ���
*        [ids]       �������飬���룬��ǩ�㱻�����ҿ��շ����ı�ı�ʶ�б�
*        [datatimes] �������飬���룬ʵʱ��ֵʱ���б�
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ������Ϊ 0
*        [values]    ˫���ȸ��������飬���룬ʵʱ��������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ������Ϊ 0
*        [states]    64 λ�������飬���룬ʵʱ������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ������Ϊ 0
*        [qualities] ���������飬���룬ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�����д��ʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע�����ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*/
typedef 
golden_error 
(*gos_snaps_event)(
                   golden_int32 count,
                   const golden_int32 *ids, 
                   const golden_int32 *datetimes, 
                   const golden_int16 *ms, 
                   const golden_float64 *values,
                   const golden_int64 *states,
                   const golden_int16 *qualities,
                   const golden_error *errors
                   );
/*
 * ��ǩ����ոı�֪ͨ���Ļص��ӿ�
 */
typedef gos_snaps_event gos_data_change;

/**
* ������gos_snaps_event_ex
* ���ܣ���ǩ����ոı�֪ͨ���Ļص��ӿ�
* ������
*        [event_type]  �޷������Σ����룬֪ͨ���ͣ��ο�ö�� GOLDEN_EVENT_TYPE
*        [handle]      ���ͣ����룬����֪ͨ�ľ��
*        [param]       voidָ�룬���룬�û�����gos_subscribe_snapshots_exʱparam����
*        [count]       ���ͣ����룬
*                      ��ʾ ids��datetimes��ms��values��states��qualities��errors�ĳ���
*        [ids]         �������飬���룬��ǩ�㱻�����ҿ��շ����ı�ı�ʶ�б�
*        [datatimes]   �������飬���룬ʵʱ��ֵʱ���б�
*                      ��ʾ����1970��1��1��08:00:00������
*        [ms]          ���������飬���룬ʵʱ��ֵʱ���б�
*                      ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ������Ϊ 0
*        [values]      ˫���ȸ��������飬���룬ʵʱ��������ֵ�б�
*                      ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ������Ϊ 0
*        [states]      64 λ�������飬���룬ʵʱ������ֵ�б�
*                      ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                      GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ������Ϊ 0
*        [qualities]   ���������飬���룬ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY
*        [errors]      �޷����������飬�����д��ʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע�����ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*/
typedef
golden_error
(*gos_snaps_event_ex)(
golden_uint32 event_type,
golden_int32 handle,
void* param,
                   golden_int32 count,
                   const golden_int32 *ids, 
                   const golden_int32 *datetimes, 
                   const golden_int16 *ms, 
                   const golden_float64 *values,
                   const golden_int64 *states,
                   const golden_int16 *qualities,
                   const golden_error *errors
                   );


/**
* ������goh_data_playback
* ���ܣ���ǩ����ʷ���ݻطŻص��ӿ�
* ������
*        [count]     ���ͣ����룬
*                    ��ʾ ids��datetimes��ms��values��states��qualities��errors�ĳ���
*        [ids]       �������飬���룬�������ݵı�ʶ�б�
*        [datatimes] �������飬���룬������ֵʱ���б�
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬������ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ��
*        [values]    ˫���ȸ��������飬���룬����ĸ�������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ���ݡ�
*        [states]    64 λ�������飬���룬�����������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ���ݡ�
*        [x]         32 λ�����������룬��ά�����xֵ��������������Ϊ GOLDEN_COOR �ı�ǩ�㣬�����Ӧ���ݡ�
*        [y]         32 λ�����������룬��ά�����yֵ��������������Ϊ GOLDEN_COOR �ı�ǩ�㣬�����Ӧ���ݡ�
*        [qualities] ���������飬���룬�������ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [error]     �޷������ͣ�������緵��GoE_DATA_PLAYBACK_DONE����������һ�λطţ�����ֻ�᷵��GoE_OK��
* ��ע�����ӿڶ���������Ϊ GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*/
typedef 
golden_error 
(*goh_data_playback)(
                     golden_int32 count,
                     const golden_int32 *ids, 
                     const golden_int32 *datetimes, 
                     const golden_int16 *ms, 
                     const golden_float64 *values,
                     const golden_int64 *states,
                     const golden_float32 *x,
                     const golden_float32 *y,
                     const golden_int16 *qualities,
                     const golden_error *error
                     );
/**
* ������goh_data_playback
* ���ܣ���ǩ����ʷ���ݻطŻص��ӿ�
* ������
*        [count]     ���ͣ����룬
*                    ��ʾ ids��datetimes��ms��values��states��qualities��errors�ĳ���
*        [ids]       �������飬���룬�������ݵı�ʶ�б�
*        [datatimes] �������飬���룬������ֵʱ���б�
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬������ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ��
*        [values]    ˫���ȸ��������飬���룬����ĸ�������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ���ݡ�
*        [states]    64 λ�������飬���룬�����������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ���ݡ�
*        [x]         32 λ�����������룬��ά�����xֵ��������������Ϊ GOLDEN_COOR �ı�ǩ�㣬�����Ӧ���ݡ�
*        [y]         32 λ�����������룬��ά�����yֵ��������������Ϊ GOLDEN_COOR �ı�ǩ�㣬�����Ӧ���ݡ�
*        [qualities] ���������飬���룬�������ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY
*        [error]     �޷������ͣ�������緵��GoE_DATA_PLAYBACK_DONE����������һ�λطţ�����ֻ�᷵��GoE_OK��
* ��ע�����ӿڶ���������Ϊ GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*/
typedef 
golden_error 
(*goh_data_playback_ex)(
golden_uint32 event_type,
golden_int32 handle,
void* param,
golden_int32 count,
const golden_int32 *ids,
const golden_int32 *datetimes,
const golden_int16 *ms,
const golden_float64 *values,
const golden_int64 *states,
const golden_float32 *x,
const golden_float32 *y,
const golden_int16 *qualities,
const golden_error *error
);

typedef
golden_error
(*gob_named_type_remove_event_ex)(
  golden_uint32 event_type,
  golden_int32 handle,
  void* param,
  const char* name
  );

typedef 
golden_error 
(*gob_named_type_create_event_ex)(
  golden_uint32 event_type,
  golden_int32 handle,
  void* param,
  const char* name,
  long field_count,
  const GOLDEN_DATA_TYPE_FIELD* fields
  );

typedef 
  golden_error 
  (*go_connect_event)(
    golden_int32 count,
    const GOLDEN_CONNECT_EVENT* const* event,
    const char* const* pre_call,
    const char* const* post_call
  );

typedef
golden_error
(*go_connect_event_ex)(
  golden_uint32 event_type,
  golden_int32 handle,
  void* param,
  golden_int32 count,
  const GOLDEN_CONNECT_EVENT* const* event,
  const char* const* pre_call,
  const char* const* post_call
);


#ifdef WIN32
#ifdef _WIN64
#include <math.h>
double inline _golden_sqrt(double d)
{
  return sqrt(d);
}
#else
double inline __declspec (naked) __fastcall _golden_sqrt(double)
{
  _asm fld qword ptr [esp+4]
  _asm fsqrt
  _asm ret 8
}
#endif
#endif

#define GOLDEN_ABS(V1, V2)                          ( (V1) > (V2) ? ((V1) - (V2)) : ((V2) - (V1)) )
#define GOLDEN_MAX(V1, V2)                          ( (V1) > (V2) ? (V1) : (V2) )
#define GOLDEN_MIN(V1, V2)                          ( (V1) < (V2) ? (V1) : (V2) )
#define GOLDEN_TIME_LESS_THAN(S1, MS1, S2, MS2)     ( S1 < S2 ? true : ( S1 == S2 ? ( MS1 < MS2 ? true : false ) : false ) )
#define GOLDEN_TIME_EQUAL_TO(S1, MS1, S2, MS2)      ( S1 == S2 ? ( MS1 == MS2 ? true : false ) : false )
#define GOLDEN_TIME_GREATER_THAN(S1, MS1, S2, MS2)  ( S1 > S2 ? true : ( S1 == S2 ? ( MS1 > MS2 ? true : false ) : false ) )
#define GOLDEN_TIME_EQUAL_OR_LESS_THAN(S1, MS1, S2, MS2)     ( S1 < S2 ? true : ( S1 == S2 ? ( MS1 <= MS2 ? true : false ) : false ) )
#define GOLDEN_TIME_EQUAL_OR_GREATER_THAN(S1, MS1, S2, MS2)  ( S1 > S2 ? true : ( S1 == S2 ? ( MS1 >= MS2 ? true : false ) : false ) )
#define GOLDEN_MS_DELAY_BETWEEN(S1, MS1, S2, MS2)   ( (unsigned long long)(S1 - S2) * 1000 + (unsigned long long)(MS1 - MS2) )
#define GOLDEN_MS_ADD_TIME(S1, MS1, MSES, S2, MS2)  { \
                                                      unsigned long long mses__ = MSES + MS1; \
                                                      S2 = S1 + static_cast<int>(mses__ / 1000); \
                                                      MS2 = static_cast<short>(mses__ % 1000); }
#define GOLDEN_MS_SUB_TIME(S1, MS1, MSES, S2, MS2)  { \
                                                      golden_int32 subs__  = static_cast<golden_int32>(MSES / 1000);  \
                                                      golden_int16 subms__ = static_cast<golden_int16>(MSES % 1000);\
                                                      S2 = (MS1 < subms__ ? S1 - subs__ - 1 : S1 - subs__); \
                                                      MS2 = (MS1 < subms__ ? MS1 + 1000 - subms__ : MS1 - subms__);}
#define GOLDEN_DISTANCE(X1, Y1, X2, Y2)             _golden_sqrt( GOLDEN_ABS(X1, X2) * GOLDEN_ABS(X1, X2) + GOLDEN_ABS(Y1, Y2) * GOLDEN_ABS(Y1, Y2) )


// 3.0.3400
#define GOLDEN_API_MAJOR_VERSION      3
#define GOLDEN_API_MINOR_VERSION      0
#define GOLDEN_API_BETA_VERSION       3400

#endif /* __GOLDEN_H__ */
