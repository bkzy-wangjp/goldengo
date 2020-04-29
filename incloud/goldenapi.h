#ifndef __GOLDEN_API_H__
#define __GOLDEN_API_H__

#include "golden.h"
#include "golden_error.h" 

/************************************ API ���ýӿ� ************************************/

/**
* ������go_get_api_version 
* ���ܣ�ȡ�� goldenapi ��İ汾��
* ������
*      [major]        ���ͣ���������汾��
*      [minor]        ���ͣ�������ΰ汾��
*      [beta]         ���ͣ�����������汾��
* ��ע��������صİ汾���� golden.h �ж���Ĳ�ƥ��(GOLDEN_API_XXX_VERSION)����Ӧ�ó���ʹ���˴���Ŀ⡣
*      Ӧ���һ��������Ϣ���˳�����������ڵ���ĳЩ api ʱ�ᵼ�±�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_api_version(
                   golden_int32 *major,
                   golden_int32 *minor, 
                   golden_int32 *beta
                   );

/**
* ������go_set_option 
* ���ܣ����� api ��Ϊ����
* ������
*      [type]        ���ͣ����룬ѡ����𣬲μ�ö�� GOLDEN_API_OPTION
*      [value]       ���ͣ����룬ѡ��ֵ��
* ��ע��ѡ�����ú�����һ�ε��� api ʱ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_set_option(
              golden_int32 type,
              golden_int32 value 
              );

GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  go_create_datagram_handle(
  golden_int32 port,
  const char* remotehost,
  golden_datagram_handle& handle
  );

GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  go_remove_datagram_handle(
  golden_datagram_handle handle
  );

GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  go_recv_datagram(
  char* message,
  golden_int32& message_len,
  golden_datagram_handle handle,
  char* remote_addr,
  golden_int32 timeout=-1
  );

/************************************ �������ӿ� ************************************/

GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  go_subscribe_connect(
  golden_int32 handle,
  go_connect_event callback
  );

GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
go_subscribe_connect_ex(
  golden_int32 handle,
  golden_uint32 options,
  void* param,
  go_connect_event_ex callback
);

GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  go_cancel_subscribe_connect(
  golden_int32 handle
  );

/**
* ������go_connect
* ���ܣ�����ͬ GOLDEN ���ݿ����������
* ������
*      [hostname]     �ַ��������룬GOLDEN ����ƽ̨�������������ַ�������
*      [port]         ���ͣ����룬ȱʡֵ 6327�����Ӷ˿�
*      [handle]       ���ͣ���������Ӿ��
* ��ע���ڵ������еĽӿں���֮ǰ�������ȵ��ñ���������ͬGolden�����������ӡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_connect(
           const char *hostname, 
           golden_int32 port,
           golden_int32 *handle
           );

/**
* ������go_connection_count
* ���ܣ����� GOLDEN ��������ǰ���Ӹ���
* ������
*      [handle]   ���Ӿ��
*      [count]    ���ͣ���������ص�ǰ�������Ӹ���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_connection_count(
                    golden_int32 handle, 
                    golden_int32 *count
                    );
/**
* ������go_get_connections
* ���ܣ��г� GOLDEN ���������������Ӿ��
* ������
*      [handle]    ���Ӿ��
*      [sockets]   �������飬������������ӵ��׽��־��
*      [count]     ���ͣ�����/����������ʾsockets�ĳ��ȣ������ʾ���ص����Ӹ���
* ��ע���û��뱣֤����� sockets �Ŀռ��� count ���
*      �������� count С������� count����ֻ���ز�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_connections(
                   golden_int32 handle,
                   golden_int32 *sockets ,
                   golden_int32 *count
                   );
/**
* ������go_get_own_connection
* ���ܣ���ȡ��ǰ���ӵ�socket���
* ������
*      [handle]    ���Ӿ��
*      [socket]   ���ͣ��������ǰ���ӵ��׽��־��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_get_own_connection(
                golden_int32 handle,
                golden_int32* socket
                );
/**
* ������go_get_connection_info
* ���ܣ����� GOLDEN ������ָ�����ӵ���Ϣ
* ������
*      [handle]  ���Ӿ��
*      [socket]  ���ͣ����룬ָ��������
*      [info]    GOLDEN_HOST_CONNECT_INFO �ṹ�����룬��������ص���Ϣ
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_connection_info(
                       golden_int32 handle, 
                       golden_int32 socket,
                       GOLDEN_HOST_CONNECT_INFO *info
                       );

/**
* ������go_disconnect
* ���ܣ��Ͽ�ͬ GOLDEN ����ƽ̨������
* ������
*      [handle]   ���Ӿ��
* ��ע����ɶ� GOLDEN �ķ��ʺ���ñ������Ͽ����ӡ�
*      ����һ���Ͽ�������Ҫ�������Ӻ���ܵ��������Ľӿں�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_disconnect(
              golden_int32 handle
              );

/**
* ������go_login
* ���ܣ�����Ч�ʻ���¼
* ������
*      [handle]    ���Ӿ��
*      [user]      �ַ��������룬��¼�ʻ�
*      [password]  �ַ��������룬�ʻ�����
*      [priv]      ���ͣ�GOLDEN_RO, GOLDEN_DW, GOLDEN_TA, GOLDEN_SA ֮һ��������ʻ�Ȩ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_login(
         golden_int32 handle,
         const char *user, 
         const char *password, 
         golden_int32 *priv
         );

/**
* ������go_get_linked_ostype
* ���ܣ���ȡ���Ӿ�������ӵķ���������ϵͳ����
* ������
*      [handle]           ���Ӿ��
*      [Golden_OS_Type]   ����ϵͳ����
* ��ע������δ�����κη�����������GOLDEN_OS_INVALID(��ǰ֧�ֲ���ϵͳ���ͣ�windows��linux)��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_get_linked_ostype(
                     golden_int32 handle,
                     Golden_OS_Type* ostype
                    );

/**
* ������go_change_password
* ���ܣ��޸��û��ʻ�����
* ������
*      [handle]        ���Ӿ��
*      [user]          �ַ��������룬�����ʻ�
*      [password]      �ַ��������룬�ʻ��¿���
* ��ע��ֻ��ϵͳ����Ա�����޸������û������롣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_change_password(
                   golden_int32 handle,
                   const char *user, 
                   const char *password
                   );

/**
* ������go_change_my_password
* ���ܣ��û��޸��Լ��ʻ�����
* ������
*      [handle]        ���Ӿ��
*      [old_pwd]       �ַ��������룬�ʻ�ԭ����
*      [new_pwd]       �ַ��������룬�ʻ��¿���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_change_my_password(
                      golden_int32 handle,
                      const char *old_pwd, 
                      const char *new_pwd
                      );


/**
* ������go_get_priv
* ���ܣ���ȡ����Ȩ��
* ������
*      [handle]    ���Ӿ��
*      [priv]      ���ͣ�GOLDEN_RO, GOLDEN_DW, GOLDEN_TA, GOLDEN_SA ֮һ��������ʻ�Ȩ��
* ��ע�������δ��½���ڷ��������������У���ӦȨ��Ϊ-1����ʾû���κ�Ȩ�ޡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_priv(
            golden_int32 handle,
            golden_int32 *priv
            );


/**
* ������go_change_priv
* ���ܣ��޸��û��ʻ�Ȩ��
* ������
*      [handle]    ���Ӿ��
*      [user]      �ַ��������룬�����ʻ�
*      [priv]      ���ͣ�GOLDEN_RO, GOLDEN_DW, GOLDEN_TA, GOLDEN_SA ֮һ�����룬�ʻ�Ȩ��
* ��ע��ֻ�й���Ա���޸�Ȩ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_change_priv(
               golden_int32 handle,
               const char *user, 
               golden_int32 priv
               );

/**
* ������go_add_user
* ���ܣ�����û��ʻ�
* ������
*      [handle]    ���Ӿ��
*      [user]      �ַ��������룬�ʻ�
*      [password]  �ַ��������룬�ʻ���ʼ����
*      [priv]      ���ͣ�GOLDEN_RO, GOLDEN_DW, GOLDEN_TA, GOLDEN_SA ֮һ�����룬�ʻ�Ȩ��
* ��ע��ֻ�й���Ա������û�Ȩ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_add_user(
            golden_int32 handle,
            const char *user,
            const char *password,
            golden_int32 priv
            );

/**
* ������go_remove_user
* ���ܣ�ɾ���û��ʻ�
* ������
*      [handle]    ���Ӿ��
*      [user]      �ַ��������룬�ʻ���
* ��ע��ֻ�й���Ա��ɾ���û�Ȩ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_remove_user(
               golden_int32 handle,
               const char *user
               );

/**
* ������go_lock_user
* ���ܣ����û�����û�
* ������
*      [handle]    ���Ӿ��
*      [user]      �ַ��������룬�ʻ���
*      [lock]      ���������룬�Ƿ����
* ��ע��ֻ�й���Ա�����ý���Ȩ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_lock_user(
golden_int32 handle,
const char *user,
bool lock
);


/**
* ������go_get_users
* ���ܣ���������û�
* ������
*      [handle]    ���Ӿ��
*      [count]     ���ͣ�����/���������ʱ��ʾ users��privs �ĳ��ȣ����û�������
*                  ���ʱ��ʾ�ɹ����ص��û���Ϣ������
*      [info]      �ṹ������ָ�룬������û���Ϣ
* ��ע���û��뱣֤����� info �Ŀռ��� count �����
*       �������� count С���ܵ��û�������ֻ���ز����û���Ϣ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_users(
             golden_int32 handle,
             golden_int32 *count,
             GOLDEN_USER_INFO *infos
             );


/**
* ������go_add_blacklist
* ���ܣ�������Ӻ�������
* ������
*      [handle]    ���Ӿ��
*      [addr]      �ַ��������룬��ֹ���Ӷε�ַ��
*      [mask]      �ַ��������룬��ֹ���Ӷ��������롣
*      [desc]      �ַ��������룬��ֹ���Ӷε�˵�������� 511 �ַ������ضϡ�
* ��ע��addr �� mask �����������γ�һ��������
*      ���Ը�������Χ�ڵ����Ӷ�������ֹ�������������ȼ������������ӣ�
*      ��������Ӽ�λ�ں������У�Ҳλ�����������У��������ȱ���ֹ��
*      ��Ч��������������� 1 λ�� 0 ��࣬���磺"255.255.254.0"��
*      ��ȫ��Ϊ 1 ʱ����ʾ��������ֻ�� addr һ����ַ��������ȫ��Ϊ 0��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_add_blacklist(
                 golden_int32 handle,
                 const char *addr, 
                 const char *mask, 
                 const char *desc
                 );


/**
* ������go_update_blacklist
* ���ܣ������������Ӻ�������
* ������
*      [handle]    ���Ӿ��
*      [addr]      �ַ��������룬ԭ��ֹ���Ӷε�ַ��
*      [mask]      �ַ��������룬ԭ��ֹ���Ӷ��������롣
*      [addr_new]  �ַ��������룬�µ���ֹ���Ӷε�ַ��
*      [mask_new]  �ַ��������룬�µ���ֹ���Ӷ��������롣
*      [desc]      �ַ��������룬�µ���ֹ���Ӷε�˵�������� 511 �ַ������ضϡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_update_blacklist(
                    golden_int32 handle,
                    const char *addr, 
                    const char *mask, 
                    const char *addr_new, 
                    const char *mask_new, 
                    const char *desc
                    );

/**
* ������go_remove_blacklist
* ���ܣ�ɾ�����Ӻ�������
* ������
*      [handle]    ���Ӿ��
*      [addr]      �ַ��������룬��ֹ���Ӷε�ַ��
*      [mask]      �ַ��������룬��ֹ���Ӷ��������롣
* ��ע��ֻ�� addr �� mask ��ȫ��ͬ����Ϊͬһ����ֹ���ӶΡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_remove_blacklist(
                    golden_int32 handle,
                    const char *addr, 
                    const char *mask
                    );

/**
* ������go_get_blacklist
* ���ܣ�������Ӻ�����
* ������
*      [handle]    ���Ӿ��
*      [addrs]     �ַ���ָ�����飬�������ֹ���Ӷε�ַ�б�
*      [masks]     �ַ���ָ�����飬�������ֹ���Ӷ����������б�
*      [descs]     �ַ���ָ�����飬�������ֹ���Ӷε�˵����
*      [count]     ���ͣ�����/������û�����
* ��ע���û��뱣֤����� addrs, masks, descs �Ŀռ��� count �����
*      �������� count С������� count����ֻ���ز�����ֹ���ӶΣ�
*      addrs, masks ��ÿ���ַ���ָ����ָ�������ߴ粻��С�� 32 �ֽڣ�
*      descs ��ÿ���ַ���ָ����ָ�������ߴ粻��С�� 512 �ֽڡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_blacklist(
                 golden_int32 handle,
                 char* const* addrs,
                 char* const* masks, 
                 char* const* descs, 
                 golden_int32 *count
                 );


/**
* ������go_add_authorization
* ���ܣ�����������Ӷ�
* ������
*      [handle]    ���Ӿ��
*      [addr]      �ַ��������룬�������Ӷε�ַ��
*      [mask]      �ַ��������룬�������Ӷ��������롣
*      [priv]      ���������룬�������Ӷ�ӵ�е��û�Ȩ�ޡ�
*      [desc]      �ַ��������룬�������Ӷε�˵�������� 511 �ַ������ضϡ�
* ��ע��addr �� mask �����������γ�һ��������
*        ���Ը�������Χ�ڵ����Ӷ�����Ϊ�����εģ�
*        ���Բ��õ�¼ (go_login)����ֱ�ӵ��� API�� 
*        ����ӵ�е�Ȩ���� priv ��ָ����
*        ��Ч��������������� 1 λ�� 0 ��࣬
*        ���磺"255.255.254.0"����ȫ��Ϊ 1 ʱ��
*        ��ʾ��������ֻ�� addr һ����ַ��
*        ������ȫ��Ϊ 0��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_add_authorization(
                     golden_int32 handle,
                     const char *addr, 
                     const char *mask, 
                     golden_int32 priv, 
                     const char *desc
                     );


/**
* ������go_update_authorization
* ���ܣ������������Ӷ�
* ������
*      [handle]    ���Ӿ��
*      [addr]      �ַ��������룬ԭ�������Ӷε�ַ��
*      [mask]      �ַ��������룬ԭ�������Ӷ��������롣
*      [addr_new]  �ַ��������룬�µ��������Ӷε�ַ��
*      [mask_new]  �ַ��������룬�µ��������Ӷ��������롣
*      [priv]      ���������룬�µ��������Ӷ�ӵ�е��û�Ȩ�ޡ�
*      [desc]      �ַ��������룬�µ��������Ӷε�˵�������� 511 �ַ������ضϡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_update_authorization(
                        golden_int32 handle,
                        const char *addr, 
                        const char *mask, 
                        const char *addr_new, 
                        const char *mask_new, 
                        golden_int32 priv, 
                        const char *desc
                        );

/**
* ������go_remove_authorization
* ���ܣ�ɾ���������Ӷ�
* ������
*      [handle]    ���Ӿ��
*      [addr]      �ַ��������룬�������Ӷε�ַ��
*      [mask]      �ַ��������룬�������Ӷ��������롣
* ��ע��ֻ�� addr �� mask ��ȫ��ͬ����Ϊͬһ���������ӶΡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_remove_authorization(
                        golden_int32 handle,
                        const char *addr, 
                        const char *mask
                        );

/**
* ������go_get_authorizations
* ���ܣ���������������Ӷ�
* ������
*      [handle]    ���Ӿ��
*      [addrs]     �ַ���ָ�����飬������������Ӷε�ַ�б�
*      [masks]     �ַ���ָ�����飬������������Ӷ����������б�
*      [privs]     �������飬������������Ӷ�Ȩ���б�
*      [descs]     �ַ���ָ�����飬������������Ӷε�˵����
*      [count]     ���ͣ�����/������û�����
* ��ע���û��뱣֤����� addrs, masks, privs, descs �Ŀռ��� count �����
*        �������� count С������� count����ֻ���ز����������ӶΣ�
*        addrs, masks ��ÿ���ַ���ָ����ָ�������ߴ粻��С�� 32 �ֽڣ�
*        descs ��ÿ���ַ���ָ����ָ�������ߴ粻��С�� 512 �ֽڡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_authorizations(
                      golden_int32 handle,
                      char* const* addrs,
                      char* const* masks, 
                      golden_int32 *privs, 
                      char* const* descs, 
                      golden_int32 *count
                      );
/**
* ������go_release_pointer
* ���ܣ��ͷŴ�goldenapi���Զ�������char*ָ��
* ������
*      [handle]    ���Ӿ��
*      [pointer]     �ַ���ָ�룬���룬���������ʱ *pointer ����Ϊ�գ����ʱ *pointerΪ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_release_pointer(golden_int32 handle, char** pointer);

/**
* ������go_host_time
* ���ܣ���ȡ GOLDEN ��������ǰUTCʱ��
* ������
*      [handle]       ���Ӿ��
*      [hosttime]     ���ͣ������Golden�������ĵ�ǰUTCʱ�䣬
*                     ��ʾ����1970��1��1��08:00:00��������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_host_time(
             golden_int32 handle, 
             golden_int32 *hosttime
             );

/**
* ������go_format_timespan
* ���ܣ�����ʱ����ֵ����ʱ���ʽ�ַ���
* ������
*      [str]          �ַ����������ʱ���ʽ�ַ���������: 
*                     "1d" ��ʾʱ����Ϊ24Сʱ��
*                     ���庬��μ� go_parse_timespan ע�͡�
*      [timespan]     ���ͣ����룬Ҫ�����ʱ����������
* ��ע���ַ�����������С��ӦС�� 32 �ֽڡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_format_timespan(
                   char *str, 
                   golden_int32 timespan
                   );

/**
* ������go_parse_timespan
* ���ܣ�����ʱ���ʽ�ַ�������ʱ����ֵ
* ������
*      [str]          �ַ��������룬ʱ���ʽ�ַ������������£�
*                     [time_span]
*
*                     ʱ���Ȳ��ֿ��Գ��ֶ�Σ�
*                     ���õ�ʱ���ȴ��뼰�������£�
*                     ?y            ?��, 1�� = 365��
*                     ?m            ?��, 1�� = 30 ��
*                     ?d            ?��
*                     ?h            ?Сʱ
*                     ?n            ?����
*                     ?s            ?��
*                     ���磺"1d" ��ʾʱ����Ϊ24Сʱ��
*
*      [timespan]     ���ͣ���������ؽ����õ���ʱ����������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_parse_timespan(
                  const char *str, 
                  golden_int32 *timespan
                  );

/**
* ������go_parse_time
* ���ܣ�����ʱ���ʽ�ַ�������ʱ��ֵ
* ������
*      [str]          �ַ��������룬ʱ���ʽ�ַ������������£�
*                     base_time [[+|-] offset_time]
*
*                     ���� base_time ��ʾ����ʱ�䣬��������ʽ��
*                     1. ʱ���ַ������� "2010-1-1" �� "2010-1-1 8:00:00"��
*                     2. ʱ����룬��ʾ�ͻ������ʱ�䣻
*                     ���õ�ʱ����뼰�������£�
*                     td             �������
*                     yd             �������
*                     tm             �������
*                     mon            ����һ���
*                     tue            ���ܶ����
*                     wed            ���������
*                     thu            ���������
*                     fri            ���������
*                     sat            ���������
*                     sun            ���������
*                     3. �Ǻ�('*')����ʾ�ͻ��˵�ǰʱ�䡣
*
*                     offset_time �ǿ�ѡ�ģ����Գ��ֶ�Σ�
*                     ���õ�ʱ��ƫ�ƴ��뼰�������£�
*                     [+|-] ?y            ƫ��?��, 1�� = 365��
*                     [+|-] ?m            ƫ��?��, 1�� = 30 ��
*                     [+|-] ?d            ƫ��?��
*                     [+|-] ?h            ƫ��?Сʱ
*                     [+|-] ?n            ƫ��?����
*                     [+|-] ?s            ƫ��?��
*                     [+|-] ?ms           ƫ��?����
*                     ���磺"*-1d" ��ʾ��ǰʱ�̼�ȥ24Сʱ��
*
*      [datetime]     ���ͣ���������ؽ����õ���ʱ��ֵ��
*      [ms]           �����ͣ���������ؽ����õ���ʱ�����ֵ��
*  ��ע��ms ����Ϊ��ָ�룬��Ӧ�ĺ�����Ϣ�����ٷ��ء�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_parse_time(
              const char *str, 
              golden_int64 *datetime, 
              golden_int16 *ms 
              );

/**
* ������go_format_message
* ���ܣ���ȡ Golden API ���÷���ֵ�ļ������
* ������
*      [ecode]        �޷������ͣ����룬Golden API���ú�ķ���ֵ�����golden_error.hͷ�ļ�
*      [message]      �ַ�������������ش�����������
*      [name]         �ַ�������������ش����������
*      [size]         ���ͣ����룬message �������ֽڳ���
* ��ע���û��뱣֤����� message�� name �Ŀռ��� size ���, 
*      name �� message ����Ϊ��ָ�룬��Ӧ����Ϣ�����ٷ��ء�
*/
GOLDENAPI
void  
GOLDENAPI_CALLRULE 
go_format_message(
                  golden_error ecode, 
                  char *message, 
                  char *name, 
                  golden_int32 size
                  );

/**
* ������go_job_message
* ���ܣ���ȡ����ļ������
* ������
*      [job_id]       ���ͣ����룬GOLDEN_HOST_CONNECT_INFO::job �ֶ�����ʾ��������������
*      [desc]         �ַ����������������������
*      [name]         �ַ����������������������
*      [size]         ���ͣ����룬desc��name �������ֽڳ���
* ��ע���û��뱣֤����� desc��name �Ŀռ��� size ����� 
*      name �� message ����Ϊ��ָ�룬��Ӧ����Ϣ�����ٷ��ء�
*/
GOLDENAPI
void  
GOLDENAPI_CALLRULE 
go_job_message(
               golden_int32 job_id, 
               char *desc,
               char *name, 
               golden_int32 size
               );

/**
* ������go_set_timeout
* ���ܣ��������ӳ�ʱʱ��
* ������
*      [handle]   ���Ӿ��
*      [socket]   ���ͣ����룬Ҫ���ó�ʱʱ�������
*      [timeout]  ���ͣ����룬��ʱʱ�䣬��λΪ�룬0 ��ʾʼ�ձ���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_set_timeout(
               golden_int32 handle,  
               golden_int32 socket ,
               golden_int32 timeout
               );

/**
* ������go_get_timeout
* ���ܣ�������ӳ�ʱʱ��
* ������
*      [handle]   ���Ӿ��
*      [socket]   ���ͣ����룬Ҫ��ȡ��ʱʱ�������
*      [timeout]  ���ͣ��������ʱʱ�䣬��λΪ�룬0 ��ʾʼ�ձ���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_timeout(
               golden_int32 handle, 
               golden_int32 socket,
               golden_int32 *timeout
               );

/**
* ������go_kill_connection
* ���ܣ��Ͽ���֪����
* ������
*      [handle]    ���Ӿ��
*      [socket]    ���ͣ����룬Ҫ�Ͽ�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_kill_connection(
                   golden_int32 handle, 
                   golden_int32 socket
                   );

/**
* ������go_get_db_info1
* ���ܣ�����ַ��������ݿ�ϵͳ����
* ������
*      [handle]    ���Ӿ��
*      [index]     ���ͣ����룬Ҫȡ�õĲ����������μ�ö�� GOLDEN_DB_PARAM_INDEX��
*      [str]       �ַ����ͣ���������ȡ�õ��ַ�������ֵ��
*      [size]      ���ͣ����룬�ַ����������ߴ硣
* ��ע�����ӿ�ֻ���� [GOLDEN_PARAM_STR_FIRST, GOLDEN_PARAM_STR_LAST) ��Χ֮�ڲ���������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_db_info1(
                golden_int32 handle,
                golden_int32 index, 
                char *str, 
                golden_int32 size
                );

/**
* ������go_get_db_info2
* ���ܣ�����������ݿ�ϵͳ����
* ������
*      [handle]    ���Ӿ��
*      [index]     ���ͣ����룬Ҫȡ�õĲ����������μ�ö�� GOLDEN_DB_PARAM_INDEX��
*      [value]     �޷������ͣ���������ȡ�õ����Ͳ���ֵ��
* ��ע�����ӿ�ֻ���� [GOLDEN_PARAM_INT_FIRST, GOLDEN_PARAM_INT_LAST) ��Χ֮�ڲ���������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_db_info2(
                golden_int32 handle,
                golden_int32 index, 
                golden_uint32 *value
                );

/**
* ������go_set_db_info1
* ���ܣ������ַ��������ݿ�ϵͳ����
* ������
*      [handle]    ���Ӿ��
*      [index]     ���ͣ����룬Ҫ���õĲ����������μ�ö�� GOLDEN_DB_PARAM_INDEX��
*                  ���У��������г���ö��ֵ���ã�
*                  GOLDEN_PARAM_AUTO_BACKUP_PATH, 
*                  GOLDEN_PARAM_SERVER_SENDER_IP, 
*      [str]       �ַ����ͣ����룬�µĲ���ֵ��
* ��ע������޸������������������� GoE_DATABASE_NEED_RESTART ��ʾ�롣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_set_db_info1(
                golden_int32 handle,
                golden_int32 index, 
                const char *str
                );

/**
* ������go_set_db_info2
* ���ܣ������������ݿ�ϵͳ����
* ������
*      [handle]    ���Ӿ��
*      [index]     ���ͣ����룬Ҫȡ�õĲ����������μ�ö�� GOLDEN_DB_PARAM_INDEX��
*                  ���У��������г���ö��ֵ���ã�
*                  GOLDEN_PARAM_SERVER_IPC_SIZE, 
*                  GOLDEN_PARAM_EQUATION_IPC_SIZE, 
*                  GOLDEN_PARAM_HASH_TABLE_SIZE, 
*                  GOLDEN_PARAM_TAG_DELETE_TIMES, 
*                  GOLDEN_PARAM_SERVER_PORT, 
*                  GOLDEN_PARAM_SERVER_SENDER_PORT, 
*                  GOLDEN_PARAM_SERVER_RECEIVER_PORT, 
*                  GOLDEN_PARAM_SERVER_MODE, 
*                  GOLDEN_PARAM_ARV_PAGES_NUMBER, 
*                  GOLDEN_PARAM_ARVEX_PAGES_NUMBER, 
*                  GOLDEN_PARAM_EXCEPTION_AT_SERVER, 
*                  GOLDEN_PARAM_EX_ARCHIVE_SIZE, 
*                  GOLDEN_PARAM_ARCHIVE_BATCH_SIZE, 
*                  GOLDEN_PARAM_ARV_ASYNC_QUEUE_SLOWER_DOOR, 
*                  GOLDEN_PARAM_ARV_ASYNC_QUEUE_NORMAL_DOOR, 
*                  GOLDEN_PARAM_INDEX_ALWAYS_IN_MEMORY, 
*                  GOLDEN_PARAM_DISK_MIN_REST_SIZE, 
*                  GOLDEN_PARAM_DELAY_OF_AUTO_MERGE_OR_ARRANGE, 
*                  GOLDEN_PARAM_START_OF_AUTO_MERGE_OR_ARRANGE, 
*                  GOLDEN_PARAM_STOP_OF_AUTO_MERGE_OR_ARRANGE, 
*                  GOLDEN_PARAM_START_OF_AUTO_BACKUP, 
*                  GOLDEN_PARAM_STOP_OF_AUTO_BACKUP, 
*                  GOLDEN_PARAM_MAX_LATENCY_OF_SNAPSHOT, 
*                  GOLDEN_PARAM_PAGE_ALLOCATOR_RESERVE_SIZE, 
*      [value]     �޷������ͣ����룬�µĲ���ֵ��
* ��ע������޸������������������� GoE_DATABASE_NEED_RESTART ��ʾ�롣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_set_db_info2(
                golden_int32 handle,
                golden_int32 index, 
                golden_uint32 value
                );

/**
* ������go_get_logical_drivers
* ���ܣ�����߼��̷�
* ������
*      [handle]     ���Ӿ��
*      [drivers]    �ַ����飬�����
*                   �����߼��̷���ɵ��ַ�����ÿ���̷�ռһ���ַ���
* ��ע��drivers ���ڴ�ռ����û�����ά��������Ӧ��С�� 32��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_logical_drivers(
                       golden_int32 handle,
                       char *drivers 
                       );

/**
* ������go_open_path
* ���ܣ���Ŀ¼�Ա�������е��ļ�����Ŀ¼��
* ������
*      [handle]       ���Ӿ��
*      [dir]          �ַ��������룬Ҫ�򿪵�Ŀ¼
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_open_path(
             golden_int32 handle,
             const char *dir 
             );

/**
* ������go_read_path
* ���ܣ���ȡĿ¼�е��ļ�����Ŀ¼
* ������
*      [handle]      ���Ӿ��
*      [path]        �ַ����飬��������ص��ļ�����Ŀ¼ȫ·��
*      [is_dir]      ����������������� 1 ΪĿ¼��0 Ϊ�ļ�
*      [atime]       �����������Ϊ�ļ�ʱ�����ط���ʱ�� 
*      [ctime]       �����������Ϊ�ļ�ʱ�����ؽ���ʱ�� 
*      [mtime]       �����������Ϊ�ļ�ʱ�������޸�ʱ�� 
*      [size]        64 λ�����������Ϊ�ļ�ʱ�������ļ���С
* ��ע��path ���ڴ�ռ����û�����ά�����ߴ�Ӧ��С�� GOLDEN_MAX_PATH��
*      ������ֵΪ GoE_BATCH_END ʱ��ʾĿ¼��������Ŀ¼���ļ��Ѿ�������ϡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_read_path(
             golden_int32 handle,
             char *path ,
             golden_int16 *is_dir,
             golden_int32 *atime,
             golden_int32 *ctime,
             golden_int32 *mtime,
             golden_int64 *size 
             );

/**
* ������go_close_path
* ���ܣ��رյ�ǰ������Ŀ¼
* ������
*      [handle]      ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_close_path(
              golden_int32 handle
              );

/**
* ������go_mkdir
* ���ܣ�����Ŀ¼
* ������
*      [handle]       ���Ӿ��
*      [dir]          �ַ��������룬�½�Ŀ¼��ȫ·��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_mkdir(
         golden_int32 handle,
         const char *dir
         );

/**
* ������go_get_file_size
* ���ܣ����ָ�����������ļ��Ĵ�С
* ������
*      [handle]     ���Ӿ��
*      [file]       �ַ��������룬�ļ���
*      [size]       64 λ������������ļ���С
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_get_file_size(
                 golden_int32 handle,
                 const char *file,
                 golden_int64 *size
                 );

/**
* ������go_read_file
* ���ܣ���ȡ��������ָ���ļ�������
* ������
*      [handle]       ���Ӿ��
*      [file]         �ַ��������룬Ҫ��ȡ���ݵ��ļ���
*      [content]      �ַ����飬������ļ�����
*      [pos]          64 λ���ͣ����룬��ȡ�ļ�����ʼλ��
*      [size]         ���ͣ�����/�����
*                     ����ʱ��ʾҪ��ȡ�ļ����ݵ��ֽڴ�С��
*                     ���ʱ��ʾʵ�ʶ�ȡ���ֽ���
* ��ע���û��뱣֤����� content �Ŀռ��� size �����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
go_read_file(
             golden_int32 handle,
             const char *file, 
             char *content,
             golden_int64 pos,
             golden_int64 *size
             );


/*
* ������go_get_max_blob_len
* ���ܣ�ȡ�����ݿ������blob��str���Ͳ�����󳤶�
* ������
*      [handle]       ���Ӿ��
*      [len]          ���Σ�����������������ݿ������blob��str���Ͳ�����󳤶�
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_get_max_blob_len(
                    golden_int32 handle,
                    golden_int32 *len
                    );

/*
* ������go_format_quality
* ���ܣ�ȡ���������Ӧ�Ķ���
* ������
*      [handle]       ���Ӿ��
*      [count]        ��������������������
*      [qualities]    �����룬�������
*      [definitions]  ���������0~255ΪGOLDEN�����루�μ�golden.h�ļ�����256~511ΪOPC�����룬����511Ϊ�û��Զ���������
*      [lens]         ����/�������
*                     ����ʱ��ʾÿ����������С
*                     ���ʱ��ʾÿ�����峤��
* OPC�������8λ��3���ֶ��壺XX XXXX XX����Ӧ�ţ�Ʒ��λ�� ��״̬λ�� �޶�λ��
* Ʒ��λ��00��Bad��01��Uncertain��10��N/A��11��Good��
* ��״̬λ�򣺲�ͬƷ��λ���Ӧ���Եķ�״̬λ��
* �޶�λ��00��Not limited��01��Low limited��10��high limited��11��Constant��
* ������֮���ö��Ÿ����������definitions�����У�ǰ������GOLDEN��OPC����USER��ʶ��˵����ǩ�����
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_format_quality(
                  golden_int32 handle,
                  golden_int32 *count,
                  golden_int16 *qualities,
                  golden_byte **definitions,
                  golden_int32 *lens
                  );

/*
* ������go_write_named_type_field_by_name
* ���ܣ�����������Զ���������ֵ���ֶε�����
* ������
*      [handle]       ���Ӿ��
*      [type_name]    �Զ������͵����ƣ����Ƴ��Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE�ĳ��ȣ����������
*      [field_name]   �Զ�����������Ҫ�����ֶε����ƣ����Ƴ��Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE�ĳ��ȣ��������
*      [field_type]   field_name�ֶε����ͣ�GOLDEN_TYPE��֧�ֵĻ������ͣ��������
*      [object]       �Զ���������ֵ�Ļ�����,����/�������
*     [object_len]   object�������ĳ���,�������
*     [field]      ��Ҫ�����ֶ���ֵ�Ļ�����,�������
*     [field_len]    �Զ����������ֶ���ֵ�Ļ����������ݵĳ���,�������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_write_named_type_field_by_name(
        golden_int32 handle,
        const char* type_name,
        const char* field_name,
        golden_int32 field_type,
        void* object,
        golden_int16 object_len,
        const void* field,
        golden_int16 field_len
        );

/*
* ������go_write_named_type_field_by_pos
* ���ܣ���λ������Զ���������ֵ���ֶε�����
* ������
*      [handle]       ���Ӿ��
*      [type_name]    �Զ������͵����ƣ����Ƴ��Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE�ĳ��ȣ����������
*      [field_pos]    �Զ�����������Ҫ�����ֶε�λ�ã�ָ�ֶ��������ֶ��е�λ�ã���0��ʼ���������
*      [field_type]   field_posλ�������ֶε����ͣ�GOLDEN_TYPE��֧�ֵĻ������ͣ��������
*      [object]       �Զ���������ֵ�Ļ�����,����/�������
*     [object_len]   object�������ĳ���,�������
*     [field]      ��Ҫ�����ֶ���ֵ�Ļ�����,�������
*     [field_len]    �Զ����������ֶ���ֵ�Ļ����������ݵĳ���,�������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_write_named_type_field_by_pos(
      golden_int32 handle,
      const char* type_name,
      golden_int32 field_pos,
      golden_int32 field_type,
      void* object,
      golden_int16 object_len,
      const void* field,
      golden_int16 field_len
      );


/*
* ������go_read_named_type_field_by_name
* ���ܣ���������ȡ�Զ���������ֵ���ֶε�����
* ������
*      [handle]       ���Ӿ��
*      [type_name]    �Զ������͵����ƣ����Ƴ��Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE�ĳ��ȣ����������
*      [field_name]   �Զ�����������Ҫ��ȡ���ֶε����ƣ����Ƴ��Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE�ĳ��ȣ��������
*      [field_type]   field_name�ֶε����ͣ�GOLDEN_TYPE��֧�ֵĻ������ͣ��������
*      [object]       �Զ���������ֵ�Ļ�����,�������
*     [object_len]   object�������ĳ���,�������
*     [field]      ����ȡ���ֶε���ֵ�Ļ�����,����/�������
*     [field_len]    field�ֶ���ֵ�������ĳ���,�������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_read_named_type_field_by_name(
      golden_int32 handle,
      const char* type_name,
      const char* field_name,
      golden_int32 field_type,
      const void* object,
      golden_int16 object_len,
      void* field,
      golden_int16 field_len
      );


/*
* ������go_read_named_type_field_by_pos
* ���ܣ���λ����ȡ�Զ���������ֵ���ֶε�����
* ������
*      [handle]       ���Ӿ��
*      [type_name]    �Զ������͵����ƣ����Ƴ��Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE�ĳ��ȣ����������
*      [field_pos]    �Զ�����������Ҫ��ȡ���ֶε�λ�ã�ָ�ֶ��������ֶ��е�λ�ã���0��ʼ���������
*      [field_type]   field_posλ�������ֶε����ͣ�GOLDEN_TYPE��֧�ֵĻ������ͣ��������
*      [object]       �Զ���������ֵ�Ļ�����,�������
*     [object_len]   object�������ĳ���,�������
*     [field]      ����ȡ���ֶε���ֵ�Ļ�����,����/�������
*     [field_len]    field�ֶ���ֵ�������ĳ���,�������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_read_named_type_field_by_pos(
        golden_int32 handle,
        const char* type_name,
        golden_int32 field_pos,
        golden_int32 field_type,
        const void* object,
        golden_int16 object_len,
        void* field,
        golden_int16 field_len
        );

/*
* ������go_named_type_name_field_check
* ���ܣ�����Զ����������Ƽ��ֶ������Ƿ���Ϲ���
* ����1. ֻ����ʹ��26��Ӣ����ĸ,����0-9���»��ߣ�
*       2. ��������ĸ��Ϊ����ĸ��
*       3. ��Сд�����С�
* ������
*      [check_name]   ��Ҫ��������
*      [flag]         ��־0--�������ƣ����� -- �ֶ����ƣ��ݲ�����
*/

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
go_named_type_name_field_check(
  const char* check_name,
  golden_byte flag = 0
  );

/*
* ������go_judge_connect_status
* ���ܣ��ж������Ƿ���ã�
* ������
*      [handle]   ���Ӿ��
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  go_judge_connect_status(golden_int32 handle);

/**
* ������go_format_ipaddr
* ���ܣ�������IPת��Ϊ�ַ�����ʽ��IP
* ������
*      [ip]        �޷������ͣ����룬���ε�IP��ַ
*      [ip_addr]      �ַ�����������ַ���IP��ַ������
*      [size]         ���ͣ����룬ip_addr �������ֽڳ���
* ��ע���û��뱣֤����� ip_addr �Ŀռ��� size ���
*/
GOLDENAPI
void
GOLDENAPI_CALLRULE
go_format_ipaddr(golden_uint32 ip, char* ip_addr, golden_int32 size);

/************************************ ������ǩ����Ϣ�ӿ� ************************************/

/**
* ������gob_get_equation_by_file_name
* ���ܣ������ļ�����ȡ����ʽ
* ������
*      [handle]   ���Ӿ��
*      [file_name] ���룬�ַ���������ʽ·��
*      [equation]  ��������صķ���ʽ�����ΪGOLDEN_MAX_EQUATION_SIZE-1
*	
*��ע���û�����ʱΪequation����Ŀռ䲻��С��GOLDEN_MAX_EQUATION_SIZE
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_get_equation_by_file_name(
												     golden_int32 handle,
												     const char* file_name,
												     char equation[GOLDEN_MAX_EQUATION_SIZE]
												     );

/**
* ������gob_get_equation_by_id
* ���ܣ���ID����ȡ����ʽ
* ������
*      [handle]   ���Ӿ��
*      [id]				���룬���ͣ�����ʽID
*      [equation] ��������صķ���ʽ�����ΪGOLDEN_MAX_EQUATION_SIZE-1
*	
*��ע���û�����ʱΪequation����Ŀռ䲻��С��GOLDEN_MAX_EQUATION_SIZE
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_get_equation_by_id(
											 golden_int32 handle,
											 golden_int32 id,
											 char equation[GOLDEN_MAX_EQUATION_SIZE]
											 );


/**
* ������gob_append_table
* ���ܣ�����±�
* ������
*      [handle]   ���Ӿ��
*      [field]    GOLDEN_TABLE �ṹ������/���������Ϣ��
*                 ������ʱ��type��name��desc �ֶ���Ч��
*                 ���ʱ��id �ֶ���ϵͳ�Զ����䲢���ظ��û���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_append_table(
                 golden_int32 handle,
                 GOLDEN_TABLE *field
                 );

/**
* ������gob_tables_count
* ���ܣ�ȡ�ñ�ǩ�������
* ������
*      [handle]   ���Ӿ��
*      [count]    ���ͣ��������ǩ�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_tables_count(
                 golden_int32 handle, 
                 golden_int32 *count
                 );

/**
* ������gob_get_tables
* ���ܣ�ȡ�����б�ǩ����ID
* ������
*      [handle]   ���Ӿ��
*      [ids]      �������飬�������ǩ����id
*      [count]    ���ͣ�����/�����
*                 �����ʾ ids �ĳ��ȣ������ʾ��ǩ������
* ��ע���û��뱣֤����� ids �Ŀռ��� count ���
*      �������� count С������� count����ֻ���ز��ֱ�id
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_tables(
               golden_int32 handle,
               golden_int32 *ids, 
               golden_int32 *count
               );

/**
* ������gob_get_table_size_by_id
* ���ܣ����ݱ� id ��ȡ���а����ı�ǩ������
* ������
*      [handle]   ���Ӿ��
*      [id]       ���ͣ����룬��ID
*      [size]     ���ͣ���������б�ǩ������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_table_size_by_id(
                         golden_int32 handle,
                         golden_int32 id, 
                         golden_int32 *size
                         );

/**
* ������gob_get_table_size_by_name
* ���ܣ����ݱ����ƻ�ȡ���а����ı�ǩ������
* ������
*      [handle]   ���Ӿ��
*      [name]     �ַ��������룬������
*      [size]     ���ͣ���������б�ǩ������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_table_size_by_name(
                           golden_int32 handle,
                           const char *name, 
                           golden_int32 *size
                           );

/**
* ������gob_get_table_real_size_by_id
* ���ܣ����ݱ� id ��ȡ����ʵ�ʰ����ı�ǩ������
* ������
*      [handle]   ���Ӿ��
*      [id]       ���ͣ����룬��ID
*      [size]     ���ͣ���������б�ǩ������
* ע�⣺ͨ����API��ȡ��ǩ��������Ȼ�������˱��еı�ǩ��õ����������ܻ᲻һ�£��������ڷ����ڲ����������ȡ���첽�ķ�ʽ��
*       һ���������ʹ��gob_get_table_size_by_id����ȡ���еı�ǩ��������
*/
GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  gob_get_table_real_size_by_id(
  golden_int32 handle,
  golden_int32 id, 
  golden_int32 *size
  );

/**
* ������gob_get_table_property_by_id
* ���ܣ����ݱ�ǩ��� id ��ȡ������
* ������
*      [handle] ���Ӿ��
*      [field]  GOLDEN_TABLE �ṹ������/�������ǩ������ԣ�
*               ����ʱָ�� id �ֶΣ����ʱ���� type��name��desc �ֶΡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_table_property_by_id(
                             golden_int32 handle,
                             GOLDEN_TABLE *field
                             );

/**
* ������gob_get_table_property_by_name
* ���ܣ����ݱ�����ȡ��ǩ�������
* ������
*      [handle] ���Ӿ��
*      [field]  GOLDEN_TABLE �ṹ������/�������ǩ�������
*               ����ʱָ�� name �ֶΣ����ʱ���� id��type��desc �ֶΡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_table_property_by_name(
                               golden_int32 handle,
                               GOLDEN_TABLE *field
                               );

/**
* ������gob_insert_point
* ���ܣ�ʹ�����������Լ�������������ǩ��
* ������
*      [handle] ���Ӿ��
*      [base] GOLDEN_POINT �ṹ������/�����
*      ����� id, createdate, creator, changedate, changer �ֶ���������ֶΣ���� id �ֶΡ�
*      [scan] GOLDEN_SCAN_POINT �ṹ�����룬�ɼ���ǩ����չ���Լ���
*      [calc] GOLDEN_CALC_POINT �ṹ�����룬�����ǩ����չ���Լ���
* ��ע������½��ı�ǩ��û�ж�Ӧ����չ���Լ�������Ϊ��ָ�롣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_insert_point(
                 golden_int32 handle, 
                 GOLDEN_POINT *base, 
                 GOLDEN_SCAN_POINT *scan, 
                 GOLDEN_CALC_POINT *calc
                 );


/**
* ������gob_insert_max_point
* ���ܣ�ʹ����󳤶ȵ��������Լ�������������ǩ��
* ������
*      [handle] ���Ӿ��
*      [base] GOLDEN_POINT �ṹ������/�����
*      ����� id, createdate, creator, changedate, changer �ֶ���������ֶΣ���� id �ֶΡ�
*      [scan] GOLDEN_SCAN_POINT �ṹ�����룬�ɼ���ǩ����չ���Լ���
*      [calc] GOLDEN_MAX_CALC_POINT �ṹ�����룬�����ǩ����չ���Լ���
* ��ע������½��ı�ǩ��û�ж�Ӧ����չ���Լ�������Ϊ��ָ�롣
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_insert_max_point(
										 golden_int32 handle,
										 GOLDEN_POINT *base,
										 GOLDEN_SCAN_POINT *scan,
										 GOLDEN_MAX_CALC_POINT *calc
										 );

/**
* ������gob_insert_base_point
* ����  ʹ����С�����Լ�������������ǩ��
* ������
*      [handle]     ���Ӿ��
*      [tag]        �ַ��������룬��ǩ������
*      [type]       ���ͣ����룬��ǩ���������ͣ�ȡֵ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��
*                   GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64��
*                   GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64��GOLDEN_COOR��GOLDEN_STRING��GOLDEN_BLOB ֮һ��
*      [table_id]   ���ͣ����룬��ǩ�������� id
*      [use_ms]     �����ͣ����룬��ǩ��ʱ������ȣ�0 Ϊ�룻1 Ϊ���롣
*      [point_id]   ���ͣ��������ǩ�� id
* ��ע����ǩ����������Խ�ȡĬ��ֵ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_insert_base_point(
                      golden_int32 handle, 
                      const char *tag, 
                      golden_int32 type, 
                      golden_int32 table_id, 
                      golden_int16 use_ms, 
                      golden_int32 *point_id
                      );

/**
* ������gob_insert_named_type_point
* ���ܣ�ʹ�����������Լ������������Զ����������ͱ�ǩ��
* ������
*      [handle] ���Ӿ��
*      [base] GOLDEN_POINT �ṹ������/�����
*      ����� id, createdate, creator, changedate, changer �ֶ���������ֶΣ���� id �ֶΡ�
*      [scan] GOLDEN_SCAN_POINT �ṹ�����룬�ɼ���ǩ����չ���Լ���
*      [name] �ַ��������룬�Զ����������͵����֡�
* ��ע������½��ı�ǩ��û�ж�Ӧ����չ���Լ�������Ϊ��ָ�롣
*/
GOLDENAPI
  golden_error 
  GOLDENAPI_CALLRULE 
  gob_insert_named_type_point(
  golden_int32 handle, 
  GOLDEN_POINT *base, 
  GOLDEN_SCAN_POINT *scan, 
  const char* name
  );

/**
* ������gob_remove_point_by_id
* ���ܣ����� id ɾ��������ǩ��
* ������
*      [handle] ���Ӿ��
*      [id]     ���ͣ����룬��ǩ���ʶ
* ��ע��ͨ�����ӿ�ɾ���ı�ǩ��Ϊ�ɻ��ձ�ǩ�㣬
*        ����ͨ�� gob_recover_point �ӿڻָ���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_remove_point_by_id(
                       golden_int32 handle,
                       golden_int32 id
                       );

/**
* ������gob_remove_point_by_name
* ���ܣ����ݱ�ǩ��ȫ��ɾ��������ǩ��
* ������[handle]        ���Ӿ��
*        [table_dot_tag]  �ַ��������룬��ǩ��ȫ���ƣ�"����.��ǩ����"
* ��ע��ͨ�����ӿ�ɾ���ı�ǩ��Ϊ�ɻ��ձ�ǩ�㣬
*        ����ͨ�� gob_recover_point �ӿڻָ���
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_remove_point_by_name(
                         golden_int32 handle,
                         const char *table_dot_tag
                         );

/**
* ������gob_get_points_property
* ���ܣ�������ȡ��ǩ������
* ������
*        [handle] ���Ӿ��
*        [count]  ���������룬��ʾ��ǩ�������
*        [base]   GOLDEN_POINT �ṹ���飬����/�������ǩ����������б�
*                 ����ʱ��id �ֶ�ָ����Ҫ�õ����Եı�ǩ�㣬���ʱ�������ֶη��ر�ǩ������ֵ��
*        [scan]   GOLDEN_SCAN_POINT �ṹ���飬������ɼ���ǩ����չ�����б�
*        [calc]   GOLDEN_CALC_POINT �ṹ���飬����������ǩ����չ�����б�
*        [errors] �޷����������飬�������ȡ��ǩ���Եķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤����� base��scan��calc��errors �Ŀռ��� count �����
*        ��չ���Լ� scan��calc ��Ϊ��ָ�룬��ʱ�������ض�Ӧ����չ���Լ���
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_get_points_property(
                        golden_int32 handle,
                        golden_int32 count,
                        GOLDEN_POINT *base,
                        GOLDEN_SCAN_POINT *scan,
                        GOLDEN_CALC_POINT *calc,
                        golden_error *errors
                        );


/**
* ������gob_get_max_points_property
* ���ܣ�����󳤶�������ȡ��ǩ������
* ������
*        [handle] ���Ӿ��
*        [count]  ���������룬��ʾ��ǩ�������
*        [base]   GOLDEN_POINT �ṹ���飬����/�������ǩ����������б�
*                 ����ʱ��id �ֶ�ָ����Ҫ�õ����Եı�ǩ�㣬���ʱ�������ֶη��ر�ǩ������ֵ��
*        [scan]   GOLDEN_SCAN_POINT �ṹ���飬������ɼ���ǩ����չ�����б�
*        [calc]   GOLDEN_MAX_CALC_POINT �ṹ���飬����������ǩ����չ�����б�
*        [errors] �޷����������飬�������ȡ��ǩ���Եķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤����� base��scan��calc��errors �Ŀռ��� count �����
*        ��չ���Լ� scan��calc ��Ϊ��ָ�룬��ʱ�������ض�Ӧ����չ���Լ���
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_get_max_points_property(
														golden_int32 handle,
														golden_int32 count,
														GOLDEN_POINT *base,
														GOLDEN_SCAN_POINT *scan,
														GOLDEN_MAX_CALC_POINT *calc,
														golden_error *errors
														);



/**
* ������gob_search
* ���ܣ��������������ı�ǩ�㣬ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [tablemask]     �ַ��������룬��ǩ����������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [mode]          ���ͣ�GOLDEN_SORT_BY_TABLE��GOLDEN_SORT_BY_TAG��GOLDEN_SORT_BY_ID ֮һ��
*                        �������������ģʽ�����룬ȱʡֵΪGOLDEN_SORT_BY_TABLE
*        [ids]           �������飬����������������ı�ǩ���ʶ�б�
*        [count]         ���ͣ�����/���������ʱ��ʾ ids �ĳ��ȣ����ʱ��ʾ�������ı�ǩ�����
* ��ע���û��뱣֤����� ids �Ŀռ��� count ������������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��tablemask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*",
*        ���������������ͨ���ո�ָ�������"demo_*1 demo_*2"���Ὣ����demo_*1����demo_*2�����ı�ǩ������������
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_search(
           golden_int32 handle,
           const char *tagmask,
           const char *tablemask,
           const char *source,
           const char *unit,
           const char *desc,
           const char *instrument,
           golden_int32 mode,
           golden_int32 *ids, 
           golden_int32 *count
          );

/**
* ������gob_search_in_batches
* ���ܣ����������������������ı�ǩ�㣬ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [start]         ���ͣ����룬������ʼλ�ã�ָ������������ʼ������
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [tablemask]     �ַ��������룬��ǩ����������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [mode]          ���ͣ�GOLDEN_SORT_BY_TABLE��GOLDEN_SORT_BY_TAG��GOLDEN_SORT_BY_ID ֮һ��
*                        �������������ģʽ�����룬ȱʡֵΪGOLDEN_SORT_BY_TABLE
*        [ids]           �������飬����������������ı�ǩ���ʶ�б�
*        [count]         ���ͣ�����/���������ʱ��ʾ ids �ĳ��ȣ����ʱ��ʾ�������ı�ǩ�����
* ��ע���û��뱣֤����� ids �Ŀռ��� count ������������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��tablemask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*"��
*        ���������ı�ǩ�������ṩ��ҪСʱ����ʾ�������һ�����������ı�ǩ�� (��ȫ���������),
*        ���������������ͨ���ո�ָ�������"demo_*1 demo_*2"���Ὣ����demo_*1����demo_*2�����ı�ǩ������������
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_search_in_batches(
                      golden_int32 handle,
                      golden_int32 start, 
                      const char *tagmask,
                      const char *tablemask,
                      const char *source,
                      const char *unit,
                      const char *desc,
                      const char *instrument,
                      golden_int32 mode,
                      golden_int32 *ids, 
                      golden_int32 *count
                      );


/**
* ������gob_search_ex
* ���ܣ��������������ı�ǩ�㣬ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [tablemask]     �ַ��������룬��ǩ����������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [typemask]      �ַ����������������ǩ���������ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_TYPE_NAME_SIZE,
*                        ���õ���ͨ�������Ϳ���ʹ�� bool��uint8��datetime���ַ�����ʾ�������ִ�Сд��֧��ģ��������
*        [classofmask]   ���ͣ������������ǩ������ȱʡ����Ϊ-1����ʾ�������������͵ı�ǩ�㣬
*                        ��ʹ�ñ�ǩ��������Ϊ��������ʱ��������GOLDEN_CLASSö���е�һ����߶������ϡ�
*        [timeunitmask]  ���ͣ������������ǩ���ʱ������ȣ�ȱʡ����Ϊ-1����ʾ����������ʱ������ȣ�
*                        ��ʹ�ô�ʱ���������Ϊ��������ʱ��timeunitmask��ֵ����Ϊ0��1��0��ʾʱ�������Ϊ�룬1��ʾ����
*        [othertypemask] ���ͣ����������ʹ��������ǩ��������Ϊ����������ȱʡ����Ϊ0����ʾ����Ϊ����������
*                        ��ʹ�ô˲�����Ϊ��������ʱ��othertypemaskvalue��Ϊ��Ӧ������ֵ��
*                        �˲�����ȡֵ���Բο�golden.h�ļ��е�GOLDEN_SEARCH_MASK��
*        [othertypemaskvalue]
*                        �ַ����������������ʹ��������ǩ��������Ϊ��������ʱ���˲�����Ϊ��Ӧ������ֵ��ȱʡ����Ϊ0����ʾ����Ϊ����������
*                        ���othertypemask��ֵΪ0������GOLDEN_SEARCH_NULL����˲���������,
*                        ��othertypemask��Ӧ�ı�ǩ������Ϊ��ֵ����ʱ��������ֵֻ֧������жϣ�
*                        ��othertypemask��Ӧ�ı�ǩ������Ϊ�ַ�������ʱ��������ֵ֧��ģ��������
*        [mode]          ���ͣ�GOLDEN_SORT_BY_TABLE��GOLDEN_SORT_BY_TAG��GOLDEN_SORT_BY_ID ֮һ��
*                        �������������ģʽ�����룬ȱʡֵΪGOLDEN_SORT_BY_TABLE
*        [ids]           �������飬����������������ı�ǩ���ʶ�б�
*        [count]         ���ͣ�����/���������ʱ��ʾ ids �ĳ��ȣ����ʱ��ʾ�������ı�ǩ�����
* ��ע���û��뱣֤����� ids �Ŀռ��� count ������������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��tablemask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*",
*        ���������������ͨ���ո�ָ�������"demo_*1 demo_*2"���Ὣ����demo_*1����demo_*2�����ı�ǩ������������
*/
GOLDENAPI
  golden_error  
  GOLDENAPI_CALLRULE 
  gob_search_ex(
  golden_int32 handle,
  const char *tagmask,
  const char *tablemask,
  const char *source,
  const char *unit,
  const char *desc,
  const char *instrument,
  const char *typemask,
  golden_int32 classofmask,
  golden_int32 timeunitmask,
  golden_int32 othertypemask,
  const char *othertypemaskvalue,
  golden_int32 mode,
  golden_int32 *ids, 
  golden_int32 *count
  );


/**
* ������gob_search_points_count
* ���ܣ��������������ı�ǩ�㣬ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [tablemask]     �ַ��������룬��ǩ����������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [typemask]      �ַ����������������ǩ���������ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_TYPE_NAME_SIZE,
*                        ���õ���ͨ�������Ϳ���ʹ�� bool��uint8��datetime���ַ�����ʾ�������ִ�Сд��֧��ģ��������
*        [classofmask]   ���ͣ������������ǩ������ȱʡ����Ϊ-1����ʾ�������������͵ı�ǩ�㣬
*                        ��ʹ�ñ�ǩ��������Ϊ��������ʱ��������GOLDEN_CLASSö���е�һ����߶������ϡ�
*        [timeunitmask]  ���ͣ������������ǩ���ʱ������ȣ�ȱʡ����Ϊ-1����ʾ����������ʱ������ȣ�
*                        ��ʹ�ô�ʱ���������Ϊ��������ʱ��timeunitmask��ֵ����Ϊ0��1��0��ʾʱ�������Ϊ�룬1��ʾ����
*        [othertypemask] ���ͣ����������ʹ��������ǩ��������Ϊ����������ȱʡ����Ϊ0����ʾ����Ϊ����������
*                        ��ʹ�ô˲�����Ϊ��������ʱ��othertypemaskvalue��Ϊ��Ӧ������ֵ��
*                        �˲�����ȡֵ���Բο�golden.h�ļ��е�GOLDEN_SEARCH_MASK��
*        [othertypemaskvalue]
*                        �ַ����������������ʹ��������ǩ��������Ϊ��������ʱ���˲�����Ϊ��Ӧ������ֵ��ȱʡ����Ϊ0����ʾ����Ϊ����������
*                        ���othertypemask��ֵΪ0������GOLDEN_SEARCH_NULL����˲���������,
*                        ��othertypemask��Ӧ�ı�ǩ������Ϊ��ֵ����ʱ��������ֵֻ֧������жϣ�
*                        ��othertypemask��Ӧ�ı�ǩ������Ϊ�ַ�������ʱ��������ֵ֧��ģ��������
*        [count]         ���ͣ��������ʾ�������ı�ǩ�����
* ��ע�� �������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��tablemask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*",
*        ���������������ͨ���ո�ָ�������"demo_*1 demo_*2"���Ὣ����demo_*1����demo_*2�����ı�ǩ������������
*/
GOLDENAPI
  golden_error  
  GOLDENAPI_CALLRULE 
  gob_search_points_count(
  golden_int32 handle,
  const char *tagmask,
  const char *tablemask,
  const char *source,
  const char *unit,
  const char *desc,
  const char *instrument,
  const char *typemask,
  golden_int32 classofmask,
  golden_int32 timeunitmask,
  golden_int32 othertypemask,
  const char *othertypemaskvalue,
  golden_int32 *count
  );

//////////////////////////////////////////////////////////////////////////
/**
* ������gob_get_table_field_count
* ���ܣ���ȡ���ֶ�����
* ������
*        [handle]        ���Ӿ��
*        [table_id]       GOLDEN_TABLE_NAME_ID ���ͣ����룬֧��ö����ϡ�
*        [field_count]         ���ͣ��������ʾ��ȡ�����ֶθ���
* ��ע�� table_id ����GOLDEN_TABLE_ID_BASE����ʾ���������ֶ���Ϣ������GOLDEN_TABLE_ID_SCAN����ʾ�ɼ������ֶ���Ϣ��
����GOLDEN_TABLE_ID_CALC����ʾ���������ֶ���Ϣ������ GOLDEN_TABLE_ID_BASE|GOLDEN_TABLE_ID_SCAN��ͬʱ��ʾ�������� + �ɼ�������Ϣ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_get_table_field_count(golden_int32 handle, int class_of, golden_int32* field_count);
/**
* ������gob_get_table_fields
* ���ܣ���ȡ���ֶνṹ
* ������
*        [handle]        ���Ӿ��
*        [table_id]       GOLDEN_TABLE_NAME_ID ���ͣ����룬֧��ö����ϡ�
*        [fields]       GOLDEN_TAG_FIELD���飬�������ȡ���ֶν��塣
*        [field_count]         ���ͣ�����/���������ʱ��ʾfields�����������������ʾ��ȡ�����ֶθ���
* ��ע��  table_id ����GOLDEN_TABLE_ID_BASE����ʾ���������ֶ���Ϣ������GOLDEN_TABLE_ID_SCAN����ʾ�ɼ������ֶ���Ϣ��
����GOLDEN_TABLE_ID_CALC����ʾ���������ֶ���Ϣ������ GOLDEN_TABLE_ID_BASE|GOLDEN_TABLE_ID_SCAN��ͬʱ��ʾ�������� + �ɼ�������Ϣ��
fields��������ʱ�������field_count��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_get_table_fields(golden_int32 handle, int class_of, GOLDEN_TAG_FIELD* fields, golden_int32* field_count);
/**
* ������gob_get_table_fields
* ���ܣ�ͨ����ѯ������ͳ�Ʒ��ϵ�����
* ������
*        [handle]        ���Ӿ��
*        [json_str]       �ַ��������������json��ѯ�����ַ�����
*        [json_str_size]     ���ͣ����������json�ַ������ȡ�
*        [id_count]         ���ͣ��������ʾ��ȡ���ı�ǩ�����
* ��ע�� json_str����ѯ�������ο�mongodb��ѯ������
"$lt"��"$lte"��"$gt"��"$gte"��"$ne"��"$in"��"$nin"��"$like"��"$nlike"��"$and"��"$or"�ֱ��Ӧ<��<=��>��>=�������ڡ������ڡ��������ڡ�ģ��������ģ���������������롢������
{"id" : 20} ��ʾid����20��{"id" : 20 , "tag" : "abc"}��ʾid=20 && tag=abc��{"id" : {"$gte" : 18, "$lte" : 30}} ��ʾid>=18 && id<=30��
{"id": {"$ne": 12}}��ʾid != 12��{"id" : {"$in" : [12,13,14,15]}} ��ʾid ��12,13,14,15��Χ�ڣ�
{"tag" : {"$like" : "A%"}}��ʾƥ����A��ͷ�����ݣ�{"tag" : {"$like": "%A%"}}��ʾ����tag�м����A�����ݣ�
{"$or" : [{"id" : 12}, {"tag" : {"$like" : "%a"}}]}��ʾid=12 || tag like "%a"��
{"$and" : ["id" : {"$gte" : 18, "$lte" : 30}, "tag", {"$like" : "%a"}]}��ʾȡ id>=18 && id<=30 && tag like "%a"
{"$or" : [{"$and" : ["id" : {"$gte" : 18, "$lte" : 30}, "tag" : {"$like" : "%abc%"}]}, {"$and" : ["id" : {"$gte" : 80, "$lte" : 100}, "tag" : {"$nlike" : "abc%"}]}]}
��ʾȡ ((id>=18 && id <= 30 && tag like "%abc%") || (id>=80 && id <= 100 && tag not like "abc%"))
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_search_point_id_count(golden_int32 handle, const char* json_str, const size_t& json_str_size, golden_int32* id_count);
/**
* ������gob_search_point_ids
* ���ܣ���ѯ����Ϣ���ݣ���ȡ������
* ������
*        [handle]        ���Ӿ��
*        [json_str]       �ַ��������������json��ѯ�����ַ�����
*        [json_str_size]     ���ͣ����������json�ַ������ȡ�
*        [ids]         �������飬����������������ı�ǩ���ʶ�б�
*        [id_count]         ���ͣ����룬���������ʱ��ʾ id_array �ĳ��ȣ����ʱ��ʾ�������ı�ǩ�����
* ��ע�� json_str����ѯ�������ο�mongodb��ѯ������
"$lt"��"$lte"��"$gt"��"$gte"��"$ne"��"$in"��"$nin"��"$like"��"$nlike"��"$and"��"$or"�ֱ��Ӧ<��<=��>��>=�������ڡ������ڡ��������ڡ�ģ��������ģ���������������롢������
{"id" : 20} ��ʾid����20��{"id" : 20 , "tag" : "abc"}��ʾid=20 && tag=abc��{"id" : {"$gte" : 18, "$lte" : 30}} ��ʾid>=18 && id<=30��
{"id": {"$ne": 12}}��ʾid != 12��{"id" : {"$in" : [12,13,14,15]}} ��ʾid ��12,13,14,15��Χ�ڣ�
{"tag" : {"$like" : "A%"}}��ʾƥ����A��ͷ�����ݣ�{"tag" : {"$like": "%A%"}}��ʾ����tag�м����A�����ݣ�
{"$or" : [{"id" : 12}, {"tag" : {"$like" : "%a"}}]}��ʾid=12 || tag like "%a"��
{"$and" : ["id" : {"$gte" : 18, "$lte" : 30}, "tag", {"$like" : "%a"}]}��ʾȡ id>=18 && id<=30 && tag like "%a"
{"$or" : [{"$and" : ["id" : {"$gte" : 18, "$lte" : 30}, "tag" : {"$like" : "%abc%"}]}, {"$and" : ["id" : {"$gte" : 80, "$lte" : 100}, "tag" : {"$nlike" : "abc%"}]}]}
��ʾȡ ((id>=18 && id <= 30 && tag like "%abc%") || (id>=80 && id <= 100 && tag not like "abc%"))
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_search_point_ids(golden_int32 handle, const char* json_str, const size_t& json_str_size, golden_int32* ids, golden_int32* id_count);
/**
* ������gob_append_point
* ���ܣ�������ӵ���Ϣ
* ������
*        [handle]        ���Ӿ��
*        [json_str]       �ַ��������������json�ַ�����
*        [json_str_size]     ���ͣ����������json�ַ������ȡ�
*        [id]         ���ͣ������������ӳɹ��ı�ǩ����
* ��ע�� json_str����ǩ����Ϣ��ʾ�����£�
{"tag":"456","type":3,"table":4,"desc":"456",...}
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_append_point(golden_int32 handle, const char* json_str, const size_t& json_str_size, golden_int32* id);
/**
* ������gob_update_points
* ���ܣ��������µ���Ϣ
* ������
*        [handle]        ���Ӿ��
*        [id]              ��ǩ����  
*        [json_str]       �ַ��������������json�ַ�����
*        [json_str_size]     ���ͣ����������json�ַ������ȡ�
* ��ע�� json_str����ǩ����Ϣ��ʾ�����£�
{"id":1,"tag":"tag1","desc":"tag1 desc",...}
��id�������ݣ� id��table��type��millisecond �ֶβ����޸ģ�
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_update_point(golden_int32 handle, golden_int32 id, const char* json_str, const size_t& json_str_size);
/**
* ������gob_remove_points
* ���ܣ�����ɾ������Ϣ
* ������
*        [handle]        ���Ӿ��
*        [auto_purge]       ���ͣ�����������Ƿ��Զ�����ɾ����0Ϊ��������ɾ������0������ɾ��
*        [ids]     �������飬���������ɾ����ǩ�����顣
*        [id_count]         ���ͣ�����/���������ʱ��ʾ�������������ʱ��ʾɾ���ɹ�����
*        [err_codes]         �������飬�������������Ƿ�ɹ�
* ��ע��ids��err_codes��ʼ�����ȱ������id_count������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_remove_points(golden_int32 handle, int auto_purge, const golden_int32* ids, golden_int32* id_count, golden_error* err_codes);
/**
* ������gob_search_point_props
* ���ܣ�����������ȡָ���ֶ�����
* ������
*        [handle]        ���Ӿ��
*        [json_str]       �ַ��������������json�ַ�����
*        [json_str_size]     ���ͣ����������json�ַ������ȣ�
*        [tag_count]         ������������������ػ�ȡ����ǩ������
*        [prop_size]         ���ͣ��������ʾ����json�ַ������ȣ�
*        [json_props]       �ַ������飬����ʱ *json_props��ҪΪ0�����ʱjson_propsΪjson�ַ�����
*                                 ����ʹ��go_release_pointer�ͷţ����������ڴ�й¶
* ��ע�� json_str����ѯ������ѡ�񷵻��ֶΣ�
* fields ʹ��*��ʾ���������ֶΣ�ʹ��base��ʾ����base���������ֶΣ�scan��ʾ����scan�ɼ������ֶΣ�calc��ʾ����calc���������ֶΡ�
* condition ʹ�÷����μ���gob_search_point_ids�е�����������
json_str��ʽ���£�
{"fields":["id","tag","type"],
"condition":{}
}��
json_props��ʽ���£�
[
  {"id":23,"tag":"tag1","type":1...},
  {"id":24,"tag":"tag2","type":3...},
  ...
]
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_search_point_props(golden_int32 handle, const char* json_str, const size_t& json_str_size, int* tag_count, size_t* prop_size, char** json_props);

/**
* ������gob_remove_table_by_id
* ���ܣ����ݱ� id ɾ�������б�ǩ��
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬�� id 
* ��ע��ɾ���ı��ɻָ���ɾ���ı�ǩ�����ͨ�� gob_recover_point �ӿڻָ���
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_remove_table_by_id(
                       golden_int32 handle, 
                       golden_int32 id
                       );

/**
* ������gob_remove_table_by_name
* ���ܣ����ݱ���ɾ�������б�ǩ��
* ������
*        [handle]        ���Ӿ��
*        [name]          �ַ��������룬������
* ��ע��ɾ���ı��ɻָ���ɾ���ı�ǩ�����ͨ�� gob_recover_point �ӿڻָ���
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_remove_table_by_name(
                         golden_int32 handle, 
                         const char *name
                         );

/**
* ������gob_update_point_property
* ���ܣ����µ�����ǩ������
* ������
*        [handle]        ���Ӿ��
*        [base] GOLDEN_POINT �ṹ�����룬������ǩ�����Լ���
*        [scan] GOLDEN_SCAN_POINT �ṹ�����룬�ɼ���ǩ����չ���Լ���
*        [calc] GOLDEN_CALC_POINT �ṹ�����룬�����ǩ����չ���Լ���
* ��ע����ǩ���� base ������ id �ֶ�ָ�������� id��table��type��millisecond �ֶβ����޸ģ�
*      changedate��changer��createdate��creator �ֶ���ϵͳά���������ֶξ����޸ģ�
*      ���� classof �ֶΡ���������� scan��calc ��Ϊ��ָ�룬��Ӧ����չ���Խ����ֲ��䡣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_update_point_property(
                          golden_int32 handle,
                          const GOLDEN_POINT *base,
                          const GOLDEN_SCAN_POINT *scan,
                          const GOLDEN_CALC_POINT *calc
                          );

///**
//* ������gob_update_min_point_property
//* ���ܣ�����С���ȸ��µ�����ǩ������
//* ������
//*        [handle]        ���Ӿ��
//*        [base] GOLDEN_POINT �ṹ�����룬������ǩ�����Լ���
//*        [scan] GOLDEN_SCAN_POINT �ṹ�����룬�ɼ���ǩ����չ���Լ���
//*        [calc] GOLDEN_MAX_CALC_POINT �ṹ�����룬�����ǩ����չ���Լ���
//* ��ע����ǩ���� base ������ id �ֶ�ָ�������� id��table��type��millisecond �ֶβ����޸ģ�
//*      changedate��changer��createdate��creator �ֶ���ϵͳά���������ֶξ����޸ģ�
//*      ���� classof �ֶΡ���������� scan��calc ��Ϊ��ָ�룬��Ӧ����չ���Խ����ֲ��䡣
//*/
//GOLDENAPI
//golden_error
//GOLDENAPI_CALLRULE
//gob_update_min_point_property(
//															golden_int32 handle,
//															const GOLDEN_POINT *base,
//															const GOLDEN_SCAN_POINT *scan,
//															const GOLDEN_MAX_CALC_POINT *calc
//															);

/**
* ������gob_update_max_point_property
* ���ܣ�����󳤶ȸ��µ�����ǩ������
* ������
*        [handle]        ���Ӿ��
*        [base] GOLDEN_POINT �ṹ�����룬������ǩ�����Լ���
*        [scan] GOLDEN_SCAN_POINT �ṹ�����룬�ɼ���ǩ����չ���Լ���
*        [calc] GOLDEN_MAX_CALC_POINT �ṹ�����룬�����ǩ����չ���Լ���
* ��ע����ǩ���� base ������ id �ֶ�ָ�������� id��table��type��millisecond �ֶβ����޸ģ�
*      changedate��changer��createdate��creator �ֶ���ϵͳά���������ֶξ����޸ģ�
*      ���� classof �ֶΡ���������� scan��calc ��Ϊ��ָ�룬��Ӧ����չ���Խ����ֲ��䡣
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_update_max_point_property(
															golden_int32 handle,
															const GOLDEN_POINT *base,
															const GOLDEN_SCAN_POINT *scan,
															const GOLDEN_MAX_CALC_POINT *calc
															);


/**
* ������gob_find_points
* ���ܣ����� "����.��ǩ����" ��ʽ������ȡ��ǩ���ʶ
* ������
*        [handle]           ���Ӿ��
*        [count]            ����������/���������ʱ��ʾ��ǩ�����
*                           (��table_dot_tags��ids��types��classof��use_ms �ĳ���)��
*                           ���ʱ��ʾ�ҵ��ı�ǩ�����
*        [table_dot_tags]   �ַ���ָ�����飬���룬"����.��ǩ����" �б�
*        [ids]              �������飬�������ǩ���ʶ�б�, ���� 0 ��ʾδ�ҵ�
*        [types]            �������飬�������ǩ����������
*        [classof]          �������飬�������ǩ�����
*        [use_ms]           ���������飬�����ʱ������ȣ�
*                           ���� 1 ��ʾʱ�������Ϊ���룬 Ϊ 0 ��ʾΪ�롣
* ��ע���û��뱣֤����� table_dot_tags��ids��types��classof��use_ms �Ŀռ���count�����
*        ���� types��classof��use_ms ��Ϊ��ָ�룬��Ӧ���ֶν����ٷ��ء�
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_find_points(
                golden_int32 handle, 
                golden_int32 *count, 
                const char* const* table_dot_tags,
                golden_int32 *ids,
                golden_int32 *types,
                golden_int32 *classof, 
                golden_int16 *use_ms
                );

/**
* ������gob_sort_points
* ���ܣ����ݱ�ǩ�����ֶζԱ�ǩ���ʶ��������
* ������
*        [handle]           ���Ӿ��
*        [count]            ���������룬��ʾ��ǩ�����, �� ids �ĳ���
*        [ids]              �������飬���룬��ǩ���ʶ�б�
*        [index]            ���ͣ����룬�����ֶ�ö�٣��μ� GOLDEN_TAG_FIELD_INDEX��
*                           �����ݸ��ֶζ� ID ��������
*        [flag]             ���ͣ����룬��־λ��ϣ��μ� GOLDEN_TAG_SORT_FLAG ö�٣�����
*                           GOLDEN_SORT_FLAG_DESCEND             ��ʾ�������򣬲����ñ�ʾ�������У�
*                           GOLDEN_SORT_FLAG_CASE_SENSITIVE      ��ʾ�����ַ��������ֶαȽ�ʱ��Сд���У������ñ�ʾ�����ִ�Сд��
*                           GOLDEN_SORT_FLAG_RECYCLED            ��ʾ�Կɻ��ձ�ǩ�������򣬲����ñ�ʾ��������ǩ����
*                           ��ͬ�ı�־λ��ͨ��"��"����������һ��
*                           ���Կɻ��ձ�ǩ����ʱ�������ֶ���������ʹ�ã�
*                               GOLDEN_TAG_INDEX_TIMESTAMP
*                               GOLDEN_TAG_INDEX_VALUE
*                               GOLDEN_TAG_INDEX_QUALITY
* ��ע���û��뱣֤����� ids �Ŀռ��� count ���, ��� ID ָ���ı�ǩ�������ڣ�
*        ���ǩ���߱�Ҫ��������ֶ� (��ԷǼ������з���ʽ����)�����ǽ��������������β����
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_sort_points(
                golden_int32 handle, 
                golden_int32 count, 
                golden_int32 *ids,
                golden_int32 index, 
                golden_int32 flag
                );

/**
* ������gob_update_table_name
* ���ܣ����ݱ� ID ���±����ơ�
* ������
*        [handle]    ���Ӿ��
*        [tab_id]    ���ͣ����룬Ҫ�޸ı�ı�ʶ
*        [name]      �ַ��������룬�µı�ǩ������ơ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_update_table_name(
                      golden_int32 handle, 
                      golden_int32 tab_id, 
                      const char *name
                      );

/**
* ������gob_update_table_desc_by_id
* ���ܣ����ݱ� ID ���±�������
* ������
*        [handle]    ���Ӿ��
*        [tab_id]    ���ͣ����룬Ҫ�޸ı�ı�ʶ
*        [desc]      �ַ��������룬�µı�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_update_table_desc_by_id(
                            golden_int32 handle, 
                            golden_int32 tab_id, 
                            const char *desc
                            );

/**
* ������gob_update_table_desc_by_name
* ���ܣ����ݱ����Ƹ��±�������
* ������
*        [handle]    ���Ӿ��
*        [name]      �ַ��������룬Ҫ�޸ı�����ơ�
*        [desc]      �ַ��������룬�µı��������������ʱ���볤��Ϊ�յ��ַ�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_update_table_desc_by_name(
                              golden_int32 handle, 
                              const char *name, 
                              const char *desc
                              );

/**
* ������gob_recover_point
* ���ܣ��ָ���ɾ����ǩ��
* ������
*        [handle]    ���Ӿ��
*        [table_id]  ���ͣ����룬Ҫ����ǩ��ָ����ı��ʶ
*        [point_id]  ���ͣ����룬���ָ��ı�ǩ���ʶ
* ��ע: ���ӿ�ֻ�Կɻ��ձ�ǩ��(ͨ���ӿ�gob_remove_point_by_id/gob_remove_point_by_tag)��Ч��
*        �������ı�ǩ��û�����á�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_recover_point(
                  golden_int32 handle,
                  golden_int32 table_id,
                  golden_int32 point_id
                  );

/**
* ������gob_purge_point
* ���ܣ������ǩ��
* ������
*        [handle]    ���Ӿ��
*        [id]        ���������룬Ҫ����ı�ǩ���ʶ
* ��ע: ���ӿڽ��Կɻ��ձ�ǩ��(ͨ���ӿ�gob_remove_point_by_id/gob_remove_point_by_name)��Ч��
*      �������ı�ǩ��û�����á�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_purge_point(
                golden_int32 handle,
                golden_int32 id
                );


/**
* ������gob_get_recycled_points_count
* ���ܣ���ȡ�ɻ��ձ�ǩ������
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�������ɻ��ձ�ǩ�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_recycled_points_count(
                              golden_int32 handle,
                              golden_int32 *count
                              );

/**
* ������gob_get_recycled_points
* ���ܣ���ȡ�ɻ��ձ�ǩ�� id �б�
* ������
*        [handle]    ���Ӿ��
*        [ids]       �������飬������ɻ��ձ�ǩ�� id
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡ��ǩ��ĸ�����
* ��ע���û��뱣֤ ids �ĳ����� count һ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_recycled_points(
                        golden_int32 handle, 
                        golden_int32 *ids,
                        golden_int32 *count
                        );

/**
* ������gob_search_recycle_points_count
* ���ܣ�����վ���������������ı�ǩ��ĸ�����ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [fullmask]      �ַ��������룬��ǩ��ȫ�����룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE+GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��֧�ֶ�������������Կո�ָ���
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [count]         ���ͣ��������ʾ�������ı�ǩ�����
* ��ע�� �������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��tablemask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*",
*        ���������������ͨ���ո�ָ�������"demo_*1 demo_*2"���Ὣ����demo_*1����demo_*2�����ı�ǩ������������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_search_recycle_points_count(
golden_int32 handle,
const char *fullmask,
const char *tagmask,
const char *source,
const char *unit,
const char *desc,
const char *instrument,
golden_int32 *count
);
/**
* ������gob_search_recycled_points
* ���ܣ��������������Ŀɻ��ձ�ǩ�㣬ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��
*        [tablemask]     �ַ��������룬��ǩ����������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [mode]          ���ͣ�GOLDEN_SORT_BY_TABLE��GOLDEN_SORT_BY_TAG��GOLDEN_SORT_BY_ID ֮һ��
*                        �������������ģʽ�����룬ȱʡֵΪGOLDEN_SORT_BY_TABLE
*        [ids]           �������飬����������������ı�ǩ���ʶ�б�
*        [count]         ���ͣ�����/���������ʱ��ʾ ids �ĳ��ȣ����ʱ��ʾ�������ı�ǩ�����
* ��ע���û��뱣֤����� ids �Ŀռ��� count ������������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��fullmask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*"
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_search_recycled_points(
                           golden_int32 handle,
                           const char *tagmask,
                           const char *fullmask,
                           const char *source,
                           const char *unit,
                           const char *desc,
                           const char *instrument,
                           golden_int32 mode,
                           golden_int32 *ids, 
                           golden_int32 *count
                           );

/**
* ������gob_search_recycled_points_in_batches
* ���ܣ������������������Ŀɻ��ձ�ǩ�㣬ʹ�ñ�ǩ����ʱ֧��ͨ���
* ������
*        [handle]        ���Ӿ��
*        [start]         ���ͣ����룬��������ʼλ�ã�ָ������������ʼ������
*        [tagmask]       �ַ��������룬��ǩ���������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE��
*        [fullmask]      �ַ��������룬����.��ǩ��ȫ�������룬֧��"*"��"?"ͨ�����ȱʡ����Ϊ"*"�����Ȳ��ó��� GOLDEN_TAG_SIZE*2��
*        [source]        �ַ��������룬����Դ���ϣ��ַ����е�ÿ���ַ�����ʾһ������Դ��
*                        ���ַ�����ʾ��������Դ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_DESC_SIZE��
*        [unit]          �ַ��������룬��ǩ�㹤�̵�λ���Ӽ������̵�λ�а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ���ù��̵�λ������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_UNIT_SIZE��
*        [desc]          �ַ��������룬��ǩ���������Ӽ��������а����ò����ı�ǩ�������������
*                        ���ַ�����ʾ��������������������ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_SOURCE_SIZE��
*        [instrument]    �ַ����������������ǩ���豸���ơ�ȱʡ����Ϊ�գ����Ȳ��ó��� GOLDEN_INSTRUMENT_SIZE��
*        [mode]          ���ͣ�GOLDEN_SORT_BY_TABLE��GOLDEN_SORT_BY_TAG��GOLDEN_SORT_BY_ID ֮һ��
*                        �������������ģʽ�����룬ȱʡֵΪGOLDEN_SORT_BY_TABLE
*        [ids]           �������飬����������������ı�ǩ���ʶ�б�
*        [count]         ���ͣ�����/���������ʱ��ʾ ids �ĳ��ȣ����ʱ��ʾ�������ı�ǩ�����
* ��ע���û��뱣֤����� ids �Ŀռ��� count ������������а�������������֮��Ĺ�ϵΪ"��"�Ĺ�ϵ��
*        �ð���ͨ����ı�ǩ����������������ʱ�������һ���ַ�����ͨ���(��"ai67*")����õ����������ٶȡ�
*        ��� tagmask��fullmask Ϊ��ָ�룬���ʾʹ��ȱʡ����"*"
*        ���������ı�ǩ�������ṩ��ҪСʱ����ʾ�������һ�����������ı�ǩ�� (��ȫ���������)��
*/
GOLDENAPI
golden_error  
GOLDENAPI_CALLRULE 
gob_search_recycled_points_in_batches(
                                      golden_int32 handle,
                                      golden_int32 start, 
                                      const char *tagmask,
                                      const char *fullmask,
                                      const char *source,
                                      const char *unit,
                                      const char *desc,
                                      const char *instrument,
                                      golden_int32 mode,
                                      golden_int32 *ids, 
                                      golden_int32 *count
                                      );

/**
* ������gob_get_recycled_point_property
* ���ܣ���ȡ�ɻ��ձ�ǩ�������
* ������
*        [handle]   ���Ӿ��
*        [base]     GOLDEN_POINT �ṹ������/�������ǩ��������ԡ�
                    ����ʱ���� id �ֶ�ָ��Ҫȡ�õĿɻ��ձ�ǩ�㡣
*        [scan]     GOLDEN_SCAN_POINT �ṹ���������ǩ��ɼ���չ����
*        [calc]     GOLDEN_CALC_POINT �ṹ���������ǩ�������չ����
* ��ע��scan��calc ��Ϊ��ָ�룬��Ӧ����չ��Ϣ�������ء�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_recycled_point_property(
                                golden_int32 handle, 
                                GOLDEN_POINT *base,
                                GOLDEN_SCAN_POINT *scan,
                                GOLDEN_CALC_POINT *calc
                                );

/**
* ������gob_get_recycled_max_point_property
* ���ܣ�����󳤶Ȼ�ȡ�ɻ��ձ�ǩ�������
* ������
*        [handle]   ���Ӿ��
*        [base]     GOLDEN_POINT �ṹ������/�������ǩ��������ԡ�
                    ����ʱ���� id �ֶ�ָ��Ҫȡ�õĿɻ��ձ�ǩ�㡣
*        [scan]     GOLDEN_SCAN_POINT �ṹ���������ǩ��ɼ���չ����
*        [calc]     GOLDEN_MAX_CALC_POINT �ṹ���������ǩ�������չ����
* ��ע��scan��calc ��Ϊ��ָ�룬��Ӧ����չ��Ϣ�������ء�
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_get_recycled_max_point_property(
																		golden_int32 handle,
																		GOLDEN_POINT* base,
																		GOLDEN_SCAN_POINT* scan,
																		GOLDEN_MAX_CALC_POINT* calc
																		);


/**
* ������gob_clear_recycler
* ���ܣ���ձ�ǩ�����վ
* ������
*        [handle]   ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_clear_recycler(
                   golden_int32 handle 
                   );

/**
* ������gob_subscribe_tags
* ���ܣ�������ǩ�����Ը���֪ͨ����
* ������
*        [handle]    ���Ӿ��
*        [callback]  gob_tags_change ���ͻص��ӿڣ����룬
*                    �����ĵı�ǩ�������ֵ�����仯��ɾ��ʱ�����øýӿ�֪ͨ�û�,
*                    �μ� golden.h ��ԭ�͵Ķ���
* ��ע�����ڶ��Ĳ������Ӿ�������Ƕ����ģ������������������� api��
*        ���򷵻� GoE_OTHER_SDK_DOING ����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_subscribe_tags(
                   golden_int32 handle,
                   gob_tags_change_event callback
                   );
/**
* ������gob_subscribe_tags_ex
* ���ܣ���ǩ�����Ը���֪ͨ����
* ������
*        [handle]    ���Ӿ��
*        [options]   ���ͣ����룬����ѡ��μ�ö��GOLDEN_OPTION
*                    GOLDEN_O_AUTOCONN ���Ŀͻ��������ݿ�����������жϺ��Զ�����������
*        [param]     ���룬�û�������
*                    ��Ϊgob_tags_change_ex��param����
*        [callback]  gob_tags_change_ex ���ͻص��ӿڣ����룬���ص��������ط�GoE_OKʱ�˳�����
*                    ��δ����optionsΪGOLDEN_O_AUTOCONNʱ�����ĶϿ���ʹ��GOLDEN_E_DISCONNECT
*                    ��Ϊevent_typeȡֵ���ûص��������˳����ġ�
*                    ������optionsΪGOLDEN_O_AUTOCONNʱ�����ĶϿ���ʹ��GOLDEN_E_DISCONNECT
*                    ��Ϊevent_typeȡֵ���ûص�����ֱ�����ӻָ���ص��������ط�GoE_OK��
*                    �����ж��ڼ�ص���������Ƶ��Ϊ����3��
*                    event_type����ֵ�������£�
*                      GOLDEN_E_DATA        ��ǩ�����Է�������
*                      GOLDEN_E_DISCONNECT  ���Ŀͻ��������ݿ�����Ͽ�
*                      GOLDEN_E_RECOVERY    ���Ŀͻ��������ݿ����缰���Ļָ�
*                    handle �������Ļص������Ӿ��������gob_subscribe_tags_exʱ��handle����
*                    param  �û��Զ������������gob_subscribe_tags_exʱ��param����
*                    count  event_typeΪGOLDEN_E_DATAʱ��ʾids������
*                           event_typeΪ����ֵʱ��countֵΪ0
*                    ids    event_typeΪGOLDEN_E_DATAʱ��ʾ���Ը��ĵı�ǩ��ID��������countָ��
*                           event_typeΪ����ֵʱ��idsֵΪNULL
*                    what   event_typeΪGOLDEN_E_DATAʱ��ʾ���Ա��ԭ�򣬲ο�GOLDEN_TAG_CHANGE_REASON
*                           event_typeΪ����ֵʱ��whatʱֵΪ0
* ��ע�����ڶ��Ĳ������Ӿ�������Ƕ����ģ������������������� api��
*       ���򷵻� GoE_OTHER_SDK_DOING ����
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_subscribe_tags_ex(
golden_int32 handle,
golden_uint32 options,
void* param,
gob_tags_change_event_ex callback
);
/**
* ������gob_cancel_subscribe_tags
* ���ܣ�ȡ����ǩ�����Ը���֪ͨ����
* ������
*        [handle]    ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_cancel_subscribe_tags(
                          golden_int32 handle
                          );


/**
* ������gob_create_named_type
* ���ܣ������Զ�������
* ������
*        [handle]      ���Ӿ�����������
*        [name]        �Զ������͵����ƣ����͵�Ψһ��ʾ,�����ظ������Ȳ��ܳ���GOLDEN_TYPE_NAME_SIZE���������
*        [field_count]    �Զ��������а������ֶεĸ���,�������
*        [fields]      �Զ��������а������ֶε����ԣ�GOLDEN_DATA_TYPE_FIELD�ṹ�����飬������field_count��ȣ��������
*              GOLDEN_DATA_TYPE_FIELD�е�lengthֻ��typeΪstr��blob���͵�������Ч���������ͺ���
* ��ע���Զ������͵Ĵ�С����ҪС������ҳ��С(С������ҳ��С��2/3������Ҫ�������ֶεĸ�����ÿ���ֶεĳ���)��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_create_named_type(
    golden_int32 handle,
    const char* name,
    golden_int32 field_count,
    const GOLDEN_DATA_TYPE_FIELD* fields,
    char desc[GOLDEN_DESC_SIZE]
    );

/**
* ������gob_get_named_types_count
* ���ܣ���ȡ���е��Զ������͵�����
* ������
*        [handle]      ���Ӿ�����������
*        [count]      �������е��Զ������͵�����������/�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_named_types_count(
    golden_int32 handle,
    golden_int32* count
    );

/**
* ������gob_get_all_named_types
* ���ܣ���ȡ���е��Զ�������
* ������
*        [handle]      ���Ӿ�����������
*        [count]      �������е��Զ������͵�����������/�������������:Ϊname,field_counts����ĳ��ȣ����:��ȡ��ʵ���Զ������͵ĸ���
*        [name]        �������е��Զ������͵����Ƶ����飬ÿ���Զ������͵����Ƶĳ��Ȳ�����GOLDEN_TYPE_NAME_SIZE������/�������
*              ���룺name���鳤��Ҫ����count.�����ʵ�ʻ�ȡ���Զ����������Ƶ�����
*        [field_counts]    �������е��Զ��������������ֶθ��������飬����/�������
*              ���룺field_counts���鳤��Ҫ����count�����:ʵ��ÿ���Զ����������������ֶεĸ���������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_all_named_types(
      golden_int32 handle,
      golden_int32* count,
      char* name[GOLDEN_TYPE_NAME_SIZE],
      golden_int32* field_counts
      );

/**
* ������gob_get_named_type
* ���ܣ���ȡ�Զ������͵������ֶ�
* ������
*        [handle]         ���Ӿ�����������
*        [name]           �Զ������͵����ƣ��������
*        [field_count]    ����nameָ�����Զ������͵��ֶθ���������/�������
*                         ���룺ָ��fields���鳤��.�����ʵ�ʵ�name�Զ������͵��ֶεĸ���
*        [fields]         ������name��ָ�����Զ��������������ֶ�GOLDEN_DATA_TYPE_FIELD�ṹ�����飬����/�������
*                         ���룺fields���鳤��Ҫ����count�����:GOLDEN_DATA_TYPE_FIELD�ṹ������
*        [type_size]      �����Զ�������fields�ṹ�г����ֶε��ۼӺͣ��������
*        [desc]           �Զ������͵��������������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_get_named_type(
  golden_int32 handle,
  const char* name,
  golden_int32* field_count,
  GOLDEN_DATA_TYPE_FIELD* fields,
  golden_int32* type_size,
  char desc[GOLDEN_DESC_SIZE]
  );

/**
* ������gob_remove_named_type
* ���ܣ�ɾ���Զ�������
* ������
*        [handle]      ���Ӿ�����������
*        [name]        �Զ������͵����ƣ��������
*        [reserved]      �����ֶ�,��ʱ����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_remove_named_type(
    golden_int32 handle,
    const char* name,
    golden_int32 reserved=0
    );


GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
  gob_subscribe_named_type_create_event_ex(
  golden_int32 handle,
  golden_uint32 options,
  void* param,
  gob_named_type_create_event_ex callback
  );

/**
* ������gob_cancel_subscribe_named_type_create_event
* ���ܣ�ȡ���Զ������ʹ����¼�����
* ������
*        [handle]    ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
  gob_cancel_subscribe_named_type_create_event(
  golden_int32 handle
  );

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gob_subscribe_named_type_remove_event_ex(
  golden_int32 handle,
  golden_uint32 options,
  void* param,
  gob_named_type_remove_event_ex callback
);

/**
* ������gob_cancel_subscribe_named_type_remove_event
* ���ܣ�ȡ���Զ�������ɾ���¼�����
* ������
*        [handle]    ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gob_cancel_subscribe_named_type_remove_event(
    golden_int32 handle
    );

/**
* ������gob_query_load_memory
* ���ܣ���ѯ��ǩ�����Լ��ص��ڴ��еĵ�ǰ����
* ������
*        [handle]   ���Ӿ��
*        [load_memory_flag]     ��������ص��ڴ��еĵ�ǰ����
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  gob_query_load_memory(golden_int32 handle,
  golden_int32 *load_memory_flag);

/**
* ������gob_set_load_memory
* ���ܣ����ñ�ǩ�����Լ��ص��ڴ��е�����
* ������
*        [handle]   ���Ӿ��
*        [load_memory_flag]     ����/���������ʱ����ʾҪ���õļ��ص��ڴ��е�����
*                                          ���ʱ����ʾ�ɹ����ص��ڴ��е�����
* ��ע�����ĳЩ�����гɹ����ص��ڴ棬ĳЩ�����з����ڴ�ʧ�ܣ��ͻ᷵��GoE_OUT_OF_MEMORY��
*       ��ʱ��Ҫ���ݷ��ص�load_memory_flag���ж��ǲ���ȫ������ʧ�ܡ�
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  gob_set_load_memory(
  golden_int32 handle ,
  golden_int32 *load_memory_flag);

/**
* ������gob_query_need_memory_size
* ���ܣ���ѯ�������ü��ص��ڴ��еı�ǩ��������ռ�õ��ڴ�
* ������
*        [handle]   ���Ӿ��
*        [load_memory_flag]     ���룬������Ҫ�����ڴ������
*        [need_memory_size]     �������Ҫռ���ڴ���ֽ�������λ��byte
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  gob_query_need_memory_size(golden_int32 handle, golden_int32 *load_memory_flag, golden_int64* need_memory_size);

/**
* ������gob_get_named_type_names_property
* ���ܣ����ݱ�ǩ��id��ѯ��ǩ������Ӧ���Զ������͵����ֺ��ֶ�����
* ������
*        [handle]           ���Ӿ��
*        [count]            ����/�������ǩ�������
*                           ����ʱ��ʾ ids��named_type_names��field_counts��errors �ĳ��ȣ�
*                           ���ʱ��ʾ�ɹ���ȡ�Զ����������ֵı�ǩ�����
*        [ids]              �������飬���룬��ǩ���ʶ�б�
*        [named_type_names] �ַ������飬�������ǩ���Զ������͵�����
*        [field_counts]     �������飬�������ǩ���Զ������͵��ֶθ���
*        [errors]           �޷����������飬�������ȡ�Զ����������ֵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��named_type_names��field_counts��errors �ĳ����� count һ�¡�
*        ���ӿ�ֻ����������Ϊ GOLDEN_NAMED_T �ı�ǩ����Ч��
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_named_type_names_property(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *named_type_names,
  golden_int32 *field_counts,
  golden_error *errors
  );

/**
* ������gob_get_recycled_named_type_names_property
* ���ܣ����ݻ���վ��ǩ��id��ѯ��ǩ������Ӧ���Զ������͵����ֺ��ֶ�����
* ������
*        [handle]           ���Ӿ��
*        [count]            ����/�������ǩ�������
*                           ����ʱ��ʾ ids��named_type_names��field_counts��errors �ĳ��ȣ�
*                           ���ʱ��ʾ�ɹ���ȡ�Զ����������ֵı�ǩ�����
*        [ids]              �������飬���룬����վ��ǩ���ʶ�б�
*        [named_type_names] �ַ������飬�������ǩ���Զ������͵�����
*        [field_counts]     �������飬�������ǩ���Զ������͵��ֶθ���
*        [errors]           �޷����������飬�������ȡ�Զ����������ֵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��named_type_names��field_counts��errors �ĳ����� count һ�¡�
*        ���ӿ�ֻ����������Ϊ GOLDEN_NAMED_T �ı�ǩ����Ч��
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_recycled_named_type_names_property(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *named_type_names,
  golden_int32 *field_counts,
  golden_error *errors
  );

/**
* ������gob_get_named_type_points_count
* ���ܣ���ȡ���Զ������͵����б�ǩ�����
* ������
*        [handle]           ���Ӿ�����������
*        [name]             �Զ������͵����ƣ��������
*        [points_count]     ����nameָ�����Զ������͵ı�ǩ��������������
*/

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  gob_get_named_type_points_count(
  golden_int32 handle ,
  const char* name,
  golden_int32 *points_count);


/**
* ������gob_get_base_type_points_count
* ���ܣ���ȡ�����õĻ������͵����б�ǩ�����
* ������
*        [handle]           ���ͣ�������������Ӿ��
*        [type]             ���ͣ�������������õĻ������ͣ�������ֵ�����ǳ�GOLDEN_NAME_T���������GOLDEN_TYPEö��ֵ
*        [points_count]     ���ͣ��������������typeָ�������û������͵ı�ǩ�����
*/
GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  gob_get_base_type_points_count(
  golden_int32 handle,
  golden_int32 type,
  golden_int32 *points_count
  );

/**
* ������gob_modify_named_type
* ���ܣ��޸��Զ�����������,����,�ֶ�����,�ֶ�����
* ������
*        [handle]             ���Ӿ�����������
*        [name]               �Զ������͵����ƣ��������
*        [modify_name]        Ҫ�޸ĵ��Զ����������ƣ��������
*        [modify_desc]        Ҫ�޸ĵ��Զ������͵��������������
*        [modify_field_name]  Ҫ�޸ĵ��Զ��������ֶε����ƣ��������
*        [modify_field_desc]  Ҫ�޸ĵ��Զ��������ֶε��������������
*        [field_count]        �Զ��������ֶεĸ������������
*/

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE
  gob_modify_named_type(
  golden_int32 handle ,
  const char* name,
  const char* modify_name,
  const char* modify_desc,
  const char* modify_field_name[GOLDEN_TYPE_NAME_SIZE],
  const char* modify_field_desc[GOLDEN_DESC_SIZE],
  golden_int32 field_count);

/************************************ ʵʱ���ݽӿ� ************************************/

/**
* ������gos_get_snapshots
* ���ܣ�������ȡ��������ģ����������ֵ
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��values��states��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [datetimes] �������飬�����ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬�����ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [values]    ˫���ȸ��������飬�����ʵʱ��������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬������Ӧ�Ŀ���ֵ������Ϊ 0
*        [states]    64 λ�������飬�����ʵʱ������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬������Ӧ�Ŀ���ֵ������Ϊ 0
*        [qualities] ���������飬�����ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��values��states��qualities��errors �ĳ����� count һ�¡�
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_snapshots(
                  golden_int32 handle,
                  golden_int32 *count, 
                  const golden_int32 *ids, 
                  golden_int32 *datetimes, 
                  golden_int16 *ms,
                  golden_float64 *values, 
                  golden_int64 *states, 
                  golden_int16 *qualities,
                  golden_error *errors
                  );

/**
* ������gos_put_snapshots
* ���ܣ�����д�뿪������ģ����������ֵ
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��values��states��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ�д��ʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�ͬһ����ǩ���ʶ���Գ��ֶ�Σ�
*                    �����ǵ�ʱ��������ǵ����ġ�
*        [datetimes] �������飬���룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬��ʾ��Ӧ�ĺ���ֵ���������
*        [values]    ˫���ȸ��������飬���룬ʵʱ��������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ���������
*        [states]    64 λ�������飬���룬ʵʱ������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ���������
*        [qualities] ���������飬���룬ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�����д��ʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��values��states��qualities��errors �ĳ����� count һ�¡�
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_put_snapshots(
                  golden_int32 handle,
                  golden_int32 *count, 
                  const golden_int32 *ids,
                  const golden_int32 *datetimes,
                  const golden_int16 *ms,
                  const golden_float64 *values,
                  const golden_int64 *states,
                  const golden_int16 *qualities,
                  golden_error *errors
                  );

/**
* ������gos_fix_snapshots
* ���ܣ�����д�뿪������ģ����������ֵ
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��values��states��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ�д��ʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�ͬһ����ǩ���ʶ���Գ��ֶ�Σ�
*                    �����ǵ�ʱ��������ǵ����ġ�
*        [datetimes] �������飬���룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬��ʾ��Ӧ�ĺ���ֵ���������
*        [values]    ˫���ȸ��������飬���룬ʵʱ��������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ���������
*        [states]    64 λ�������飬���룬ʵʱ������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ�Ŀ���ֵ���������
*        [qualities] ���������飬���룬ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�����д��ʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��values��states��qualities��errors �ĳ����� count һ�¡�
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*        ��������ʱ����뵱ǰ����ʱ�����ȫ���ʱ�����滻��ǰ���յ�ֵ��������
*        ��������»���� gos_put_snapshots()
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_fix_snapshots(
                  golden_int32 handle,
                  golden_int32 *count, 
                  const golden_int32 *ids,
                  const golden_int32 *datetimes,
                  const golden_int16 *ms,
                  const golden_float64 *values,
                  const golden_int64 *states,
                  const golden_int16 *qualities,
                  golden_error *errors
                  );

/**
* ������gos_get_coor_snapshots
* ���ܣ�������ȡ����ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��x��y��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [datetimes] �������飬�����ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬�����ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [x]         �����ȸ��������飬�����ʵʱ�����ͺ�������ֵ�б�
*        [y]         �����ȸ��������飬�����ʵʱ��������������ֵ�б�
*        [qualities] ���������飬�����ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��x��y��qualities��errors �ĳ����� count һ�¡�
*        ���ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_coor_snapshots(
                       golden_int32 handle,
                       golden_int32 *count, 
                       const golden_int32 *ids, 
                       golden_int32 *datetimes,
                       golden_int16 *ms, 
                       golden_float32 *x, 
                       golden_float32 *y, 
                       golden_int16 *qualities,
                       golden_error *errors
                       );

/**
* ������gos_put_coor_snapshots
* ���ܣ�����д������ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��x��y��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [datetimes] �������飬���룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [x]         �����ȸ��������飬���룬ʵʱ�����ͺ�������ֵ�б�
*        [y]         �����ȸ��������飬���룬ʵʱ��������������ֵ�б�
*        [qualities] ���������飬���룬ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�����д��ʵʱ�������ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��x��y��qualities��errors �ĳ����� count һ�¡�
*        ���ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_put_coor_snapshots(
                       golden_int32 handle,
                       golden_int32 *count,
                       const golden_int32 *ids,
                       const golden_int32 *datetimes, 
                       const golden_int16 *ms, 
                       const golden_float32 *x, 
                       const golden_float32 *y, 
                       const golden_int16 *qualities,
                       golden_error *errors
                       );

/**
* ������gos_fix_coor_snapshots
* ���ܣ�����д������ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��x��y��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [datetimes] �������飬���룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [x]         �����ȸ��������飬���룬ʵʱ�����ͺ�������ֵ�б�
*        [y]         �����ȸ��������飬���룬ʵʱ��������������ֵ�б�
*        [qualities] ���������飬���룬ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�����д��ʵʱ�������ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��x��y��qualities��errors �ĳ����� count һ�¡�
*        ���ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*        ��������ʱ����뵱ǰ����ʱ�����ȫ���ʱ�����滻��ǰ���յ�ֵ��������
*        ��������»���� gos_put_coor_snapshots()
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_fix_coor_snapshots(
                       golden_int32 handle,
                       golden_int32 *count,
                       const golden_int32 *ids,
                       const golden_int32 *datetimes, 
                       const golden_int16 *ms, 
                       const golden_float32 *x, 
                       const golden_float32 *y, 
                       const golden_int16 *qualities,
                       golden_error *errors
                       );

/**
* ������gos_get_blob_snapshot
* ���ܣ���ȡ������/�ַ���ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ������ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ������ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [blob]      �ֽ������飬�����ʵʱ������/�ַ�����ֵ
*        [len]       �����ͣ����� / �����������/�ַ�����ֵ����
*        [quality]   �����ͣ������ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_blob_snapshot(
                      golden_int32 handle,
                      golden_int32 id, 
                      golden_int32 *datetime,
                      golden_int16 *ms, 
                      golden_byte *blob, 
                      golden_int16 *len,
                      golden_int16 *quality
                      );

/**
* ������gos_get_blob_snapshots
* ���ܣ�������ȡ������/�ַ���ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��blobs��lens��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ
*        [datetimes] �������飬�����ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬�����ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [blobs]     �ֽ���ָ�����飬�����ʵʱ������/�ַ�����ֵ
*        [lens]      ���������飬����/�����������/�ַ�����ֵ���ȣ�
*                    ����ʱ��ʾ��Ӧ�� blobs ָ��ָ��Ļ��������ȣ�
*                    ���ʱ��ʾʵ�ʵõ��� blob ���ȣ���� blob �ĳ��ȴ��ڻ��������ȣ��ᱻ�ضϡ�
*        [qualities] ���������飬�����ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_blob_snapshots(
                       golden_int32 handle,
                       golden_int32 *count, 
                       const golden_int32 *ids, 
                       golden_int32 *datetimes,
                       golden_int16 *ms, 
                       golden_byte* const* blobs, 
                       golden_int16 *lens,
                       golden_int16 *qualities, 
                       golden_error *errors 
                       );

/**
* ������gos_put_blob_snapshot
* ���ܣ�д�������/�ַ���ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ����룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ����룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [blob]      �ֽ������飬���룬ʵʱ������/�ַ�����ֵ
*        [len]       �����ͣ����룬������/�ַ�����ֵ���ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [quality]   �����ͣ����룬ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_put_blob_snapshot(
                      golden_int32 handle,
                      golden_int32 id,
                      golden_int32 datetime, 
                      golden_int16 ms, 
                      const golden_byte *blob,
                      golden_int16 len,
                      golden_int16 quality
                      );

/**
* ������gos_put_blob_snapshots
* ���ܣ�����д�������/�ַ���ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��blobs��lens��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ
*        [datetimes] �������飬���룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬��ʾ��Ӧ�ĺ���ֵ���������
*        [blobs]     �ֽ���ָ�����飬���룬ʵʱ������/�ַ�����ֵ
*        [lens]      ���������飬���룬������/�ַ�����ֵ���ȣ�
*                    ��ʾ��Ӧ�� blobs ָ��ָ��Ļ��������ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [qualities] ���������飬���룬ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_put_blob_snapshots(
                       golden_int32 handle,
                       golden_int32 *count, 
                       const golden_int32 *ids, 
                       const golden_int32 *datetimes,
                       const golden_int16 *ms, 
                       const golden_byte* const* blobs, 
                       const golden_int16 *lens,
                       const golden_int16 *qualities, 
                       golden_error *errors 
                       );

/**
* ������gos_get_datetime_snapshots
* ���ܣ�������ȡdatetime���ͱ�ǩ��ʵʱ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��dtvalues��dtlens��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ
*        [datetimes] �������飬�����ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬�����ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [dtvalues]  �ֽ���ָ�����飬�����ʵʱdatetime��ֵ
*        [dtlens]    ���������飬����/�����datetime��ֵ���ȣ�
*                    ����ʱ��ʾ��Ӧ�� dtvalues ָ��ָ��Ļ��������ȣ�
*        [qualities] ���������飬�����ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
*        [type]      �����ͣ����룬���б�ǩ�����ʾ���ͣ��硰yyyy-mm-dd hh:mm:ss.000����typeΪ1��Ĭ������1��
*                    ��yyyy/mm/dd hh:mm:ss.000����typeΪ2 
*                    �������type�����ձ�ǩ��������ʾ��������type������ʾ
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_DATETIME �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_datetime_snapshots(
                       golden_int32 handle,
                       golden_int32 *count, 
                       const golden_int32 *ids, 
                       golden_int32 *datetimes,
                       golden_int16 *ms, 
                       golden_byte* const* dtvalues , 
                       golden_int16 *dtlens,
                       golden_int16 *qualities, 
                       golden_error *errors,
                       golden_int16 type = -1
                       );

/**
* ������gos_put_datetime_snapshots
* ���ܣ���������datetime���ͱ�ǩ������
* ������
*        [handle]      ���Ӿ��
*        [count]       ���ͣ�����/�������ǩ�������
*                      ����ʱ��ʾ ids��datetimes��ms��dtvalues��dtlens��qualities��errors�ĳ��ȣ�
*                      ���ʱ��ʾ�ɹ�д��ı�ǩ�����
*        [ids]         �������飬���룬��ǩ���ʶ
*        [datatimes]   �������飬���룬ʵʱֵʱ���б�
*                      ��ʾ����1970��1��1��08:00:00������
*        [ms]          ���������飬���룬ʵʱ��ֵʱ���б�
*                      ����ʱ�侫��Ϊ����ı�ǩ�㣬��ʾ��Ӧ�ĺ���ֵ���������
*        [dtvalues]    �ֽ���ָ�����飬���룬datetime��ǩ���ֵ
*        [dtlens]      ���������飬���룬��ֵ����
*        [qualities]   ���������飬���룬ʵʱ��ֵƷ�ʣ������ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]      �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע�����ӿ�ֻ���������� GOLDEN_DATETIME �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gos_put_datetime_snapshots(
                          golden_int32 handle,
                          golden_int32 *count, 
                          const golden_int32 *ids, 
                          const golden_int32 *datetimes,
                          const golden_int16 *ms, 
                          const golden_byte* const* dtvalues, 
                          const golden_int16 *dtlens,
                          const golden_int16 *qualities, 
                          golden_error *errors 
                          );


/**
* ������gos_subscribe_snapshots
* ���ܣ�������ǩ����ոı��֪ͨ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�����������ʱ��ʾ ids��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ����ĵı�ǩ����������ó��� GOLDEN_MAX_SUBSCRIBE_SNAPSHOTS��
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [callback]  gos_snaps_event ���ͻص��ӿڣ����룬
*                    �����ĵı�ǩ��Ŀ���ֵ�����仯ʱ�����øýӿڣ�
*                    �μ� golden.h ��ԭ�͵Ķ��塣
*        [errors]    �޷����������飬�����
*                    д��ʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��errors �ĳ����� count һ�¡�
*        ���ڶ��Ŀ��յ����Ӿ�������Ƕ����ģ������������������� api��
*        ���򷵻� GoE_OTHER_SDK_DOING ����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_subscribe_snapshots(
                        golden_int32 handle,
                        golden_int32 *count,
                        const golden_int32 *ids,
                        gos_snaps_event callback,
                        golden_error *errors
                        );

/**
* ������gos_subscribe_snapshots_ex
* ���ܣ�������ǩ����ոı��֪ͨ����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�����������ʱ��ʾ ids��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ����ĵı�ǩ����������ó��� GOLDEN_MAX_SUBSCRIBE_SNAPSHOTS��
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [options]   ���ͣ����룬����ѡ��μ�ö��GOLDEN_OPTION
*                    GOLDEN_O_AUTOCONN ���Ŀͻ��������ݿ�����������жϺ��Զ�����������
*        [param]     ���룬�û�������
*                    ��Ϊgos_data_change_ex��param����
*        [callback]  gos_snaps_event_ex ���ͻص��ӿڣ����룬���ص��������ط�GoE_OKʱ�˳�����
*                    ��δ����optionsΪGOLDEN_O_AUTOCONNʱ�����ĶϿ���ʹ��GOLDEN_E_DISCONNECT
*                    ��Ϊevent_typeȡֵ���ûص��������˳����ġ�
*                    ������optionsΪGOLDEN_O_AUTOCONNʱ�����ĶϿ���ʹ��GOLDEN_E_DISCONNECT
*                    ��Ϊevent_typeȡֵ���ûص�����ֱ�����ӻָ���ص��������ط�GoE_OK��
*                    �����ж��ڼ�ص���������Ƶ��Ϊ����3��
*                    event_type����ֵ�������£�
*                      GOLDEN_E_DATA        ��ǩ����ոı�
*                      GOLDEN_E_DISCONNECT  ���Ŀͻ��������ݿ�����Ͽ�
*                      GOLDEN_E_RECOVERY    ���Ŀͻ��������ݿ����缰���Ļָ�
*                    handle �������Ļص������Ӿ��������gos_subscribe_snapshots_exʱ��handle����
*                    param  �û��Զ������������gos_subscribe_snapshots_exʱ��param����
*                    count  event_typeΪGOLDEN_E_DATAʱ��ʾids��datetimes,values�ȵ�����
*                           event_typeΪ����ֵʱ��countֵΪ0
*                    ids    event_typeΪGOLDEN_E_DATAʱ��ʾ���ոı�ı�ǩ��ID��������countָ��
*                           event_typeΪ����ֵʱ��idsֵΪNULL
*                    datetimes event_typeΪGOLDEN_E_DATAʱ��ʾ����ʱ�䣬������countָ��
*                              event_typeΪ����ֵʱ��datetimesֵΪNULL
*                    ms     event_typeΪGOLDEN_E_DATAʱ��ʾ���յĺ��룬������countָ��
*                           event_typeΪ����ֵʱ��msֵΪNULL
*                    values event_typeΪGOLDEN_E_DATAʱ��ʾ�����������Ϳ���ֵ��������countָ��
*                           event_typeΪ����ֵʱ��valuesֵΪNULL
*                    states event_typeΪGOLDEN_E_DATAʱ��ʾ�����������Ϳ���ֵ��������countָ��
*                           event_typeΪ����ֵʱ��statesֵΪNULL
*                    qualities event_typeΪGOLDEN_E_DATAʱ��ʾ���������룬������countָ��
*                           event_typeΪ����ֵʱ��qualitiesֵΪNULL
*                    errors event_typeΪGOLDEN_E_DATAʱ��ʾ���մ����룬������countָ��
*                           event_typeΪ����ֵʱ��errorsֵΪNULL
*        [errors]    �޷����������飬�����
*                    д��ʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��errors �ĳ����� count һ�¡�
*        ���ڶ��Ŀ��յ����Ӿ�������Ƕ����ģ������������������� api��
*        ���򷵻� GoE_OTHER_SDK_DOING ����
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
gos_subscribe_snapshots_ex(
golden_int32 handle,
golden_int32 *count,
const golden_int32 *ids,
golden_uint32 options,
void* param,
gos_snaps_event_ex callback,
golden_error *errors
);
/**
* ������gos_cancel_subscribe_snapshots
* ���ܣ�ȡ����ǩ����ո���֪ͨ����
* ������
*        [handle]    ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_cancel_subscribe_snapshots(
                               golden_int32 handle
                               );

/**
* ������gos_get_named_type_snapshot
* ���ܣ���ȡ�Զ������Ͳ��ĵ�������
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ������ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ������ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [object]    �ֽ������飬�����ʵʱ�Զ������ͱ�ǩ�����ֵ
*        [length]    �����ͣ�����/������Զ������ͱ�ǩ�����ֵ����
*        [quality]   �����ͣ������ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_named_type_snapshot(
    golden_int32 handle,
    golden_int32 id, 
    golden_int32 *datetime,
    golden_int16 *ms, 
    void* object, 
    golden_int16 *length,
    golden_int16 *quality
    );

/**
* ������gos_get_named_type_snapshots
* ���ܣ�������ȡ�Զ������Ͳ��Ŀ���
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��objects��lengths��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ
*        [datetimes] �������飬�����ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬�����ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [objects]   ָ�����飬������Զ������ͱ�ǩ����ֵ
*        [lengths]   ���������飬����/������Զ������ͱ�ǩ����ֵ���ȣ�
*                    ����ʱ��ʾ��Ӧ�� objects ָ��ָ��Ļ��������ȣ�
*                    ���ʱ��ʾʵ�ʵõ��� objects ���ȣ���� objects �ĳ��ȴ��ڻ��������ȣ��ᱻ�ضϡ�
*        [qualities] ���������飬�����ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_get_named_type_snapshots(
    golden_int32 handle,
    golden_int32 *count, 
    const golden_int32 *ids, 
    golden_int32 *datetimes,
    golden_int16 *ms, 
    void* const* objects, 
    golden_int16 *lengths,
    golden_int16 *qualities, 
    golden_error *errors 
    );

/**
* ������gos_put_named_type_snapshot
* ���ܣ�д�뵥���Զ������ͱ�ǩ��Ŀ���
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ����룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ����룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [object]    void�������飬���룬�Զ������ͱ�ǩ����ֵ
*        [length]    �����ͣ����룬�Զ������ͱ�ǩ����ֵ���ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [quality]   �����ͣ����룬ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_put_named_type_snapshot(
    golden_int32 handle,
    golden_int32 id,
    golden_int32 datetime, 
    golden_int16 ms, 
    const void *object,
    golden_int16 length,
    golden_int16 quality
    );

/**
* ������gos_put_named_type_snapshots
* ���ܣ�����д���Զ������ͱ�ǩ��Ŀ���
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��datetimes��ms��objects��lengths��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ�д��ʵʱֵ�ı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ
*        [datetimes] �������飬���룬ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬���룬ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬��ʾ��Ӧ�ĺ���ֵ���������
*        [objects]   void����ָ�����飬���룬�Զ������ͱ�ǩ����ֵ
*        [lengths]   ���������飬���룬�Զ������ͱ�ǩ����ֵ���ȣ�
*                    ��ʾ��Ӧ�� objects ָ��ָ��Ļ��������ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [qualities] ���������飬���룬ʵʱ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gos_put_named_type_snapshots(
    golden_int32 handle,
    golden_int32 *count, 
    const golden_int32 *ids, 
    const golden_int32 *datetimes,
    const golden_int16 *ms, 
    const void* const* objects, 
    const golden_int16 *lengths,
    const golden_int16 *qualities, 
    golden_error *errors 
    );
/************************************ �浵�ļ��ӿ� ************************************/

/**
* ������goa_get_archives_count
* ���ܣ���ȡ�浵�ļ�����
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�������浵�ļ�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_get_archives_count(
                       golden_int32 handle,
                       golden_int32 *count
                       );

/**
* ������goa_create_archive
* ���ܣ��½���ʷ�浵�ļ���׷�ӵ���ʷ���ݿ�
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ������ļ���׺��ӦΪ.rdf��
*        [mb_size]    ���ͣ����룬�ļ����ֽڴ�С����λΪ MB��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_create_archive(
                   golden_int32 handle, 
                   const char *path,
                   const char *file,
                   golden_int32 mb_size
                   );

/**
* ������goa_create_ranged_archive
* ���ܣ��½�ָ��ʱ�䷶Χ����ʷ�浵�ļ������뵽��ʷ���ݿ�
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*        [begin]      ���������룬��ʼʱ�䣬����1970��1��1��08:00:00������
*        [end]        ���������룬��ֹʱ�䣬����1970��1��1��08:00:00������
*        [mb_size]    ���ͣ����룬�ļ����ֽڴ�С����λΪ MB��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_create_ranged_archive(
                          golden_int32 handle,
                          const char *path, 
                          const char *file, 
                          golden_int32 begin, 
                          golden_int32 end, 
                          golden_int32 mb_size
                          );


/**
* ������goa_append_archive
* ���ܣ�׷�Ӵ����ϵ���ʷ�浵�ļ�����ʷ���ݿ⡣
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�������׺��ӦΪ.rdf��
*        [state]      ���ͣ����룬ȡֵ GOLDEN_ACTIVED_ARCHIVE��GOLDEN_NORMAL_ARCHIVE��
*                     GOLDEN_READONLY_ARCHIVE ֮һ����ʾ�ļ�״̬
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_append_archive(
                   golden_int32 handle,
                   const char *path,
                   const char *file, 
                   golden_int32 state
                   );

/**
* ������goa_remove_archive
* ���ܣ�����ʷ���ݿ����Ƴ���ʷ�浵�ļ���
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_remove_archive(
                   golden_int32 handle,
                   const char *path,
                   const char *file
                   );


/**
* ������goa_shift_actived
* ���ܣ��л���ļ�
* ������
*        [handle]     ���Ӿ��
* ��ע����ǰ��ļ���д��ʱ������������
*        �ı䵱ǰ��ļ���״̬Ϊ��ͨ״̬��
*        ��������ʷ���ݴ浵�ļ���Ѱ��δ��ʹ�ù���
*        ���뵽ǰ��ļ����Ҳಢ��Ϊ�״̬��
*        ���Ҳ�����ǰ��ļ��Ҳ���ļ���Ϊ�״̬��
*        ����active_archive_ָ����ļ�����������й����У�
*        ������֤���ж�д��������ͣ�ȴ���������ɡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_shift_actived(
                  golden_int32 handle
                  );

/**
* ������goa_reactive_archive
* ���ܣ�����ָ���浵�ļ�Ϊ��浵�ļ�
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�浵�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�浵�ļ�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_reactive_archive(
                     golden_int32 handle,
                     const char *path, 
                     const char *file
                     );

/**
* ������goa_get_first_archive
* ���ܣ���ȡ�׸��浵�ļ���·�������ơ�״̬����������д��ʱ�䡣
* ������
*        [handle]          ���Ӿ��
*        [path]            �ַ����飬������׸��浵�ļ���Ŀ¼·������������Ϊ GOLDEN_PATH_SIZE��
*        [file]            �ַ����飬������׸��浵�ļ������ƣ���������Ϊ GOLDEN_FILE_NAME_SIZE��
*        [state]           ���ͣ������ȡֵ GOLDEN_INVALID_ARCHIVE��GOLDEN_ACTIVED_ARCHIVE��
*                          GOLDEN_NORMAL_ARCHIVE��GOLDEN_READONLY_ARCHIVE ֮һ����ʾ�ļ�״̬
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
goa_get_first_archive(
                      golden_int32 handle,
                      char *path, 
                      char *file, 
                      golden_int32 *state
                      );

/**
* ������goa_get_next_archive
* ���ܣ���ȡ��һ���浵�ļ���·�������ơ�״̬����������д��ʱ�䡣
* ������
*        [handle]         ���Ӿ��
*        [path]           �ַ����飬����/�����
*                         �����ɵ��� goa_get_first_archive ��
*                         �ϴε��� goa_get_next_archive ���ص��ļ�Ŀ¼·����
*                         �����һ���浵�ļ���Ŀ¼·������������Ϊ GOLDEN_PATH_SIZE��
*        [file]           �ַ����飬����/�����
*                         �����ɵ��� goa_get_first_archive ��
*                         �ϴε��� goa_get_next_archive ���ص��ļ�����
*                         �����һ���浵�ļ������ƣ���������Ϊ GOLDEN_FILE_NAME_SIZE��
*        [state]          ���ͣ������ȡֵ GOLDEN_INVALID_ARCHIVE��GOLDEN_ACTIVED_ARCHIVE��
*                         GOLDEN_NORMAL_ARCHIVE��GOLDEN_READONLY_ARCHIVE ֮һ����ʾ�ļ�״̬
* ��ע���� path ��������Ϊ "END" ʱ��ʾȫ���浵�ļ��Ѿ�������ϡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_get_next_archive(
                     golden_int32 handle,
                     char *path,
                     char *file,
                     golden_int32 *state
                     );


/**
* ������goa_get_archives
* ���ܣ���ȡ�浵�ļ���·�������ơ�״̬����������д��ʱ�䡣
* ������
*        [handle]          ���Ӿ��
*        [paths]            �ַ������飬������浵�ļ���Ŀ¼·������������Ϊ GOLDEN_PATH_SIZE��
*        [files]            �ַ������飬������浵�ļ������ƣ���������Ϊ GOLDEN_FILE_NAME_SIZE��
*        [states]           �������飬�����ȡֵ GOLDEN_INVALID_ARCHIVE��GOLDEN_ACTIVED_ARCHIVE��
*                          GOLDEN_NORMAL_ARCHIVE��GOLDEN_READONLY_ARCHIVE ֮һ����ʾ�ļ�״̬
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
goa_get_archives(
               golden_int32 handle,
               golden_int32* count,
               golden_path_string* paths, 
               golden_filename_string* files, 
               golden_int32 *states
               );


GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
goa_get_archives_info(
                     golden_int32 handle,
                     golden_int32* count,
                     const golden_path_string* const paths, 
                     const golden_filename_string* const files, 
                     GOLDEN_HEADER_PAGE *infos,
                     golden_error* errors
                     );

GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
goa_get_archives_perf_data(
                     golden_int32 handle,
                     golden_int32* count,
                     const golden_path_string* const paths, 
                     const golden_filename_string* const files, 
                     GOLDEN_ARCHIVE_PERF_DATA* real_time_datas,
                     GOLDEN_ARCHIVE_PERF_DATA* total_datas,
                     golden_error* errors
                     );

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goa_get_archives_status(golden_int32 handle, golden_error* status);

/**
* ������goa_get_archive_info
* ���ܣ���ȡ�浵�ļ����丽���ļ�����ϸ��Ϣ��
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*        [file_id]    ���ͣ����룬�����ļ���ʶ��0 ��ʾ��ȡ���ļ���Ϣ��
*        [info]       GOLDEN_HEADER_PAGE �ṹ��������浵�ļ���Ϣ
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
goa_get_archive_info(
                     golden_int32 handle,
                     const char *path, 
                     const char *file, 
                     golden_int32 file_id, 
                     GOLDEN_HEADER_PAGE *info
                     );


/**
* ������goa_update_archive
* ���ܣ��޸Ĵ浵�ļ��Ŀ������
* ������
*        [handle]         ���Ӿ��
*        [path]           �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]           �ַ��������룬�ļ�����
*        [rated_capacity] ���ͣ����룬�ļ����С����λΪ MB��
*        [ex_capacity]    ���ͣ����룬�����ļ���С����λΪ MB��
*        [auto_merge]     �����ͣ����룬�Ƿ��Զ��ϲ������ļ���
*        [auto_arrange]   �����ͣ����룬�Ƿ��Զ�����浵�ļ���
* ��ע: rated_capacity �� ex_capacity ������Ϊ 0����ʾ���޸Ķ�Ӧ�������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
goa_update_archive(
                   golden_int32 handle,
                   const char *path, 
                   const char *file, 
                   golden_int32 rated_capacity, 
                   golden_int32 ex_capacity, 
                   golden_int16 auto_merge, 
                   golden_int16 auto_arrange
                   );

/**
* ������goa_merge_archive
* ���ܣ��ϲ������ļ����������ļ�
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬���ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬���ļ�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_merge_archive(
                  golden_int32 handle,
                  const char *path, 
                  const char *file
                  );

/**
* ������goa_arrange_archive
* ���ܣ�����浵�ļ�����ͬһ��ǩ������ݿ�����һ������߲�ѯЧ�ʡ�
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_arrange_archive(
                    golden_int32 handle,
                    const char *path, 
                    const char *file
                    );

/**
* ������goa_reindex_archive
* ���ܣ�Ϊ�浵�ļ������������������ڻָ����ݡ�
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*/
GOLDENAPI 
golden_error 
GOLDENAPI_CALLRULE 
goa_reindex_archive(
                    golden_int32 handle,
                    const char *path, 
                    const char *file
                    ); 

/**
* ������goa_backup_archive
* ���ܣ��������浵�ļ����丽���ļ���ָ��·��
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*        [dest]       �ַ��������룬����Ŀ¼·����������"\"��"/"��β��
*/
GOLDENAPI 
golden_error 
GOLDENAPI_CALLRULE 
goa_backup_archive(
                   golden_int32 handle,
                   const char *path, 
                   const char *file, 
                   const char *dest
                   ); 

/**
* ������goa_move_archive
* ���ܣ����浵�ļ��ƶ���ָ��Ŀ¼
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*        [dest]       �ַ��������룬�ƶ�Ŀ¼·����������"\"��"/"��β��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goa_move_archive(
golden_int32 handle,
const char *path,
const char *file,
const char *dest
);

/**
* ������goa_reindex_archive
* ���ܣ�Ϊ�浵�ļ�ת��������ʽ��
* ������
*        [handle]     ���Ӿ��
*        [path]       �ַ��������룬�ļ�����Ŀ¼·����������"\"��"/"��β��
*        [file]       �ַ��������룬�ļ�����
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goa_convert_index(
golden_int32 handle,
const char *path,
const char *file
);


/**
* ������goa_query_big_job
* ���ܣ���ѯ��������ִ�еĺ�̨�������͡�״̬�ͽ���
* ������
*        [handle]     ���Ӿ��
*        [process]    ����ѯ�Ľ��̴��ţ����̵ı�ʶ�μ�ö�� GOLDEN_PROCESS_NAME, 
*                     GOLDEN_PROCESS_HISTORIAN: ��ʷ������̣����������������ͣ�
*                         GOLDEN_MERGE: �ϲ������ļ������ļ�; 
*                         GOLDEN_ARRANGE: ����浵�ļ�; 
*                         GOLDEN_REINDEX: �ؽ�����; 
*                         GOLDEN_BACKUP: ����; 
*                         GOLDEN_REACTIVE: ����Ϊ��浵; 
*                     GOLDEN_PROCESS_EQUATION: ����ʽ������̣����������������ͣ�
*                         GOLDEN_COMPUTE: ��ʷ����; 
*                     GOLDEN_PROCESS_BASE: ��ǩ��Ϣ������̣����������������ͣ�
*                         GOLDEN_UPDATE_TABLE: �޸ı�����; 
*                         GOLDEN_REMOVE_TABLE: ɾ����; 
*        [path]       �ַ������������������Ϊ GOLDEN_PATH_SIZE��
*                     ��������������ֶα�ʾ�浵�ļ�����Ŀ¼·����
*                         GOLDEN_MERGE
*                         GOLDEN_ARRANGE
*                         GOLDEN_REINDEX
*                         GOLDEN_BACKUP
*                         GOLDEN_REACTIVE
*                     ����������������ֶα�ʾԭ���ı�����
*                         GOLDEN_UPDATE_TABLE
*                         GOLDEN_REMOVE_TABLE
*                     �����������񲻿��á�
*        [file]       �ַ������������������Ϊ GOLDEN_FILE_NAME_SIZE��
*                     ��������������ֶα�ʾ�浵�ļ�����
*                         GOLDEN_MERGE
*                         GOLDEN_ARRANGE
*                         GOLDEN_REINDEX
*                         GOLDEN_BACKUP
*                         GOLDEN_REACTIVE
*                     ����������������ֶα�ʾ�޸ĺ�ı�����
*                          GOLDEN_UPDATE_TABLE
*                     �����������񲻿��á�
*        [job]        �����ͣ����������ı�ʶ�μ�ö�� GOLDEN_BIG_JOB_NAME��
*        [state]      ���ͣ�����������ִ��״̬���ο� golden_error.h
*        [end_time]   ���ͣ��������������ʱ�䡣
*        [progress]   �����ȸ����ͣ����������Ľ��Ȱٷֱȡ�
* ��ע��path �� file �����ɴ���ָ�룬��Ӧ����Ϣ�����ٷ��ء�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goa_query_big_job(
                  golden_int32 handle,
                  golden_int32 process, 
                  char *path, 
                  char *file, 
                  golden_int16 *job, 
                  golden_int32 *state, 
                  golden_int32 *end_time, 
                  golden_float32 *progress 
                  );

/**
* ������goa_cancel_big_job
* ���ܣ�ȡ����������ִ�еĺ�̨����
* ������
*        [handle]     ���Ӿ��
*        [process]    ����ѯ�Ľ��̴��ţ����̵ı�ʶ�μ�ö�� GOLDEN_PROCESS_NAME,
*                     GOLDEN_PROCESS_HISTORIAN: ��ʷ������̣����������������ͣ�
*                         GOLDEN_MERGE: �ϲ������ļ������ļ�;
*                         GOLDEN_ARRANGE: ����浵�ļ�;
*                         GOLDEN_REINDEX: �ؽ�����;
*                         GOLDEN_BACKUP: ����;
*                         GOLDEN_REACTIVE: ����Ϊ��浵;
* ��ע����֧��ȡ��    GOLDEN_PROCESS_EQUATION: ����ʽ�������
*                     GOLDEN_PROCESS_BASE: ��ǩ��Ϣ�������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goa_cancel_big_job(golden_int32 handle, golden_int32 process);



/************************************ ��ʷ���ݽӿ� ************************************/

/**
* ������goh_archived_values_count
* ���ܣ���ȡ������ǩ����һ��ʱ�䷶Χ�ڵĴ洢ֵ����.
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ�����������Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ��ȡ
*        [ms1]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ��ʼʱ���Ӧ�ĺ��룻�������
*        [datetime2]     ���ͣ����룬��ʾ����ʱ�����������Ϊ 0����ʾ��ȡֱ���浵�����ݵ����ʱ��
*        [ms2]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ����ʱ���Ӧ�ĺ��룻�������
*        [count]         ���ͣ��������������ʱ�䷶Χ�ڵĴ洢ֵ����
* ��ע���� datetime1��ms1 �γɵ�ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_archived_values_count(
                          golden_int32 handle,
                          golden_int32 id, 
                          golden_int32 datetime1, 
                          golden_int16 ms1, 
                          golden_int32 datetime2,
                          golden_int16 ms2, 
                          golden_int32 *count
                          );

/**
* ������goh_archived_values_real_count
* ���ܣ���ȡ������ǩ����һ��ʱ�䷶Χ�ڵ���ʵ�Ĵ洢ֵ����.
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ�����������Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ��ȡ
*        [ms1]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ��ʼʱ���Ӧ�ĺ��룻�������
*        [datetime2]     ���ͣ����룬��ʾ����ʱ�����������Ϊ 0����ʾ��ȡֱ���浵�����ݵ����ʱ��
*        [ms2]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ����ʱ���Ӧ�ĺ��룻�������
*        [count]         ���ͣ��������������ʱ�䷶Χ�ڵĴ洢ֵ����
* ��ע���� datetime1��ms1 �γɵ�ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*/

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goh_archived_values_real_count(
                              golden_int32 handle,
                              golden_int32 id, 
                              golden_int32 datetime1, 
                              golden_int16 ms1, 
                              golden_int32 datetime2,
                              golden_int16 ms2, 
                              golden_int32 *count
                              );

/**
* ������goh_get_archived_values
* ���ܣ���ȡ������ǩ��һ��ʱ���ڵĴ�������
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ���ʱ����ʵ�ʵõ�����ֵ����
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������ʷ��������ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ�洢ֵ������Ϊ 0
*        [states]        64 λ�������飬�������ʷ������ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ�洢ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_archived_values(
                        golden_int32 handle,
                        golden_int32 id,
                        golden_int32 *count, 
                        golden_int32 *datetimes,
                        golden_int16 *ms, 
                        golden_float64 *values,
                        golden_int64 *states,
                        golden_int16 *qualities
                        );


/**
* ������goh_get_archived_values_backward
* ���ܣ������ȡ������ǩ��һ��ʱ���ڵĴ�������
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ���ʱ����ʵ�ʵõ�����ֵ����
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������ʷ��������ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ�洢ֵ������Ϊ 0
*        [states]        64 λ�������飬�������ʷ������ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ�洢ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_archived_values_backward(
                                 golden_int32 handle,
                                 golden_int32 id,
                                 golden_int32 *count, 
                                 golden_int32 *datetimes,
                                 golden_int16 *ms, 
                                 golden_float64 *values,
                                 golden_int64 *states,
                                 golden_int16 *qualities
                                 );

/**
* ������goh_get_archived_coor_values
* ���ܣ���ȡ������ǩ��һ��ʱ���ڵ������ʹ�������
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��x��y��qualities �ĳ��ȣ�
*                        ���ʱ����ʵ�ʵõ�����ֵ����
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [x]             �����ȸ��������飬����������ͺ�������ʷ��ֵ�б�
*        [y]             �����ȸ��������飬�������������������ʷ��ֵ�б�
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��x��y��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_archived_coor_values(
                             golden_int32 handle,
                             golden_int32 id,
                             golden_int32 *count,
                             golden_int32 *datetimes, 
                             golden_int16 *ms,
                             golden_float32 *x, 
                             golden_float32 *y, 
                             golden_int16 *qualities
                             );

/**
* ������goh_get_archived_coor_values_backward
* ���ܣ������ȡ������ǩ��һ��ʱ���ڵ������ʹ�������
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��x��y��qualities �ĳ��ȣ�
*                        ���ʱ����ʵ�ʵõ�����ֵ����
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [x]             �����ȸ��������飬����������ͺ�������ʷ��ֵ�б�
*        [y]             �����ȸ��������飬�������������������ʷ��ֵ�б�
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��x��y��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_archived_coor_values_backward(
                                      golden_int32 handle,
                                      golden_int32 id,
                                      golden_int32 *count,
                                      golden_int32 *datetimes, 
                                      golden_int16 *ms,
                                      golden_float32 *x, 
                                      golden_float32 *y, 
                                      golden_int16 *qualities
                                      );


/**
* ������goh_get_archived_values_in_batches
* ���ܣ���ʼ�Էֶη��ط�ʽ��ȡһ��ʱ���ڵĴ�������
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ�����������Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ��ȡ
*        [ms1]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ��ʼʱ���Ӧ�ĺ��룻�������
*        [datetime2]     ���ͣ����룬��ʾ����ʱ�����������Ϊ 0����ʾ��ȡֱ���浵�����ݵ����ʱ��
*        [ms2]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ����ʱ���Ӧ�ĺ��룻�������
*        [count]         ���ͣ��������������ʱ�䷶Χ�ڵĴ洢ֵ����
*        [batch_count]   ���ͣ������ÿ�ηֶη��صĳ��ȣ����ڼ������� goh_get_next_archived_values �ӿ�
* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_archived_values_in_batches(
                                   golden_int32 handle,
                                   golden_int32 id,
                                   golden_int32 datetime1,
                                   golden_int16 ms1,
                                   golden_int32 datetime2,
                                   golden_int16 ms2,
                                   golden_int32 *count,
                                   golden_int32 *batch_count
                                   );

/**
* ������goh_get_next_archived_values
* ���ܣ��ֶζ�ȡһ��ʱ���ڵĴ�������
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���Σ�����/�����
*                        ����ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ���ʱ��ʾʵ�ʵõ��Ĵ洢ֵ������
*        [datetimes]     �������飬�������ʷ��ֵʱ���б�,
*                        ��ʾ����1970��1��1��08:00:00������
*        [ms]            ���������飬�������ʷ��ֵʱ���б�
*                        ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [values]        ˫���ȸ��������飬�������ʷ��������ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬������Ӧ����ʷ�洢ֵ������Ϊ 0
*        [states]        64 λ�������飬�������ʷ������ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬������Ӧ����ʷ�洢ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count �����
*        �� count ����С�� goh_get_archived_values_in_batches �ӿ��з��ص� batch_count ��ֵ��
*        ������ GoE_BATCH_END ��ʾȫ�����ݻ�ȡ��ϡ�
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_next_archived_values(
                             golden_int32 handle,
                             golden_int32 id, 
                             golden_int32 *count, 
                             golden_int32 *datetimes, 
                             golden_int16 *ms, 
                             golden_float64 *values, 
                             golden_int64 *states,
                             golden_int16 *qualities
                             );

/**
* ������goh_get_timed_values
* ���ܣ���ȡ������ǩ��ĵ�������ʱ��������ʷ��ֵ��
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ����룬��ʾ datetimes��ms��values��states��qualities �ĳ��ȡ�
*        [datetimes]     �������飬���룬��ʾ��Ҫ�ĵ�������ʱ���б�
*                        Ϊ����1970��1��1��08:00:00������
*        [ms]            ���������飬���룬����ʱ�侫��Ϊ����ı�ǩ�㣬
*                        ��ʾ��Ҫ�ĵ�������ʱ���Ӧ�ĺ���ֵ��������ԡ�
*        [values]        ˫���ȸ��������飬�������ʷ��������ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬������Ӧ����ʷ��ֵ������Ϊ 0
*        [states]        64 λ�������飬�������ʷ������ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬������Ӧ����ʷ��ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count �����
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_timed_values(
                     golden_int32 handle, 
                     golden_int32 id, 
                     golden_int32 count, 
                     const golden_int32 *datetimes,
                     const golden_int16 *ms,
                     golden_float64 *values, 
                     golden_int64 *states,
                     golden_int16 *qualities
                     );

/**
* ������goh_get_timed_coor_values
* ���ܣ���ȡ���������ǩ��ĵ�������ʱ��������ʷ��ֵ��
* ������
*        [handle]        ���Ӿ��
*        [pt]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ����룬��ʾ datetimes��ms��x��y��qualities �ĳ��ȡ�
*        [datetimes]     �������飬���룬��ʾ��Ҫ�ĵ�������ʱ���б�
*                        Ϊ����1970��1��1��08:00:00������
*        [ms]            ���������飬���룬����ʱ�侫��Ϊ����ı�ǩ�㣬
*                        ��ʾ��Ҫ�ĵ�������ʱ���Ӧ�ĺ���ֵ��������ԡ�
*        [x]             �����ȸ��������飬����������ͺ�������ʷ��ֵ��ֵ�б�
*        [y]             �����ȸ��������飬�������������������ʷ��ֵ��ֵ�б�
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��x��y��qualities �ĳ����� count �����
*        ���ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_timed_coor_values(
                          golden_int32 handle, 
                          golden_int32 id,
                          golden_int32 count,
                          const golden_int32 *datetimes,
                          const golden_int16 *ms,
                          golden_float32 *x,
                          golden_float32 *y, 
                          golden_int16 *qualities
                          );

/**
* ������goh_get_interpo_values
* ���ܣ���ȡ������ǩ��һ��ʱ���ڵȼ����ʷ��ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ����Ҫ�Ĳ�ֵ���������ʱ����ʵ�ʵõ��Ĳ�ֵ����
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_interpo_values(
                       golden_int32 handle,
                       golden_int32 id,
                       golden_int32 *count,
                       golden_int32 *datetimes, 
                       golden_int16 *ms , 
                       golden_float64 *values,
                       golden_int64 *states,
                       golden_int16 *qualities
                       );

/**
* ������goh_get_interval_values
* ���ܣ���ȡ������ǩ��ĳ��ʱ��֮��һ�������ĵȼ���ڲ�ֵ�滻����ʷ��ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [interval]      ���ͣ����룬��ֵʱ��������λΪ����
*        [count]         ���ͣ����룬��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ����Ҫ�Ĳ�ֵ������
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�����ڴ����ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_interval_values(
                        golden_int32 handle,
                        golden_int32 id, 
                        golden_int64 interval, 
                        golden_int32 count, 
                        golden_int32 *datetimes,
                        golden_int16 *ms,
                        golden_float64 *values,
                        golden_int64 *states,
                        golden_int16 *qualities
                        );

/**
* ������goh_get_single_value
* ���ܣ���ȡ������ǩ��ĳ��ʱ�����ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [mode]          ���ͣ����룬ȡֵ GOLDEN_NEXT��GOLDEN_PREVIOUS��GOLDEN_EXACT��GOLDEN_INTER ֮һ��
*                        GOLDEN_NEXT Ѱ����һ����������ݣ�
*                        GOLDEN_PREVIOUS Ѱ����һ����������ݣ�
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*                        GOLDEN_INTER ȡָ��ʱ����ڲ�ֵ���ݡ�
*        [datetime]      ���ͣ�����/���������ʱ��ʾʱ��������
*                        ���ʱ��ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��ʾʱ������������ʱ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*                        ����������룬���ʱΪ 0��
*        [value]         ˫���ȸ��������������������ʷ��ֵ
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷֵ������Ϊ 0
*        [state]         64 λ�����������������ʷ��ֵ��
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷֵ������Ϊ 0
*        [quality]       �����ͣ��������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_single_value(
                     golden_int32 handle,
                     golden_int32 id, 
                     golden_int32 mode, 
                     golden_int32 *datetime,
                     golden_int16 *ms,
                     golden_float64 *value, 
                     golden_int64 *state,
                     golden_int16 *quality
                     );

/**
* ������goh_get_single_coor_value
* ���ܣ���ȡ������ǩ��ĳ��ʱ�����������ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [mode]          ���ͣ����룬ȡֵ GOLDEN_NEXT��GOLDEN_PREVIOUS��GOLDEN_EXACT��GOLDEN_INTER ֮һ��
*                        GOLDEN_NEXT Ѱ����һ����������ݣ�
*                        GOLDEN_PREVIOUS Ѱ����һ����������ݣ�
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*                        GOLDEN_INTER ȡָ��ʱ����ڲ�ֵ���ݡ�
*        [datetime]      ���ͣ�����/���������ʱ��ʾʱ��������
*                        ���ʱ��ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��ʾʱ������������ʱ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*                        ����������룬���ʱΪ 0��
*        [x]             �����ȸ����ͣ��������������ʷ��ֵ
*        [y]             �����ȸ����ͣ��������������ʷ��ֵ
*        [quality]       �����ͣ��������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_single_coor_value(
                          golden_int32 handle,
                          golden_int32 id,
                          golden_int32 mode,
                          golden_int32 *datetime,
                          golden_int16 *ms,
                          golden_float32 *x, 
                          golden_float32 *y, 
                          golden_int16 *quality 
                          );

/**
* ������goh_get_single_blob_value
* ���ܣ���ȡ������ǩ��ĳ��ʱ��Ķ�����/�ַ�������ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [mode]          ���ͣ����룬ȡֵ GOLDEN_NEXT��GOLDEN_PREVIOUS��GOLDEN_EXACT ֮һ��
*                        GOLDEN_NEXT Ѱ����һ����������ݣ�
*                        GOLDEN_PREVIOUS Ѱ����һ����������ݣ�
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*        [datetime]      ���ͣ�����/���������ʱ��ʾʱ��������
*                        ���ʱ��ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��ʾʱ������������ʱ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*                        ����������룬���ʱΪ 0��
*        [blob]          �ֽ������飬�����������/�ַ�����ʷֵ
*        [len]           �����ͣ�����/���������ʱ��ʾ blob �ĳ��ȣ�
*                        ���ʱ��ʾʵ�ʻ�ȡ�Ķ�����/�ַ������ݳ��ȡ�
*        [quality]       �����ͣ��������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_single_blob_value(
                          golden_int32 handle,
                          golden_int32 id, 
                          golden_int32 mode, 
                          golden_int32 *datetime,
                          golden_int16 *ms, 
                          golden_byte *blob,
                          golden_int16 *len,
                          golden_int16 *quality
                          );


/**
* ������goh_get_archived_blob_values
* ���ܣ���ȡ������ǩ���ʱ��Ķ�����/�ַ�������ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*        [count]         ���ͣ�����/����������ʾ��Ҫ��ѯ��������
*                        �����ʾʵ�ʲ鵽��������
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ��������
*        [ms1]           �����ͣ����룬ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������
*        [datetime2]     ���ͣ�����,��ʾ����ʱ��������
*        [ms2]           �����ͣ����룬ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������
*        [datetimes]     �������飬�������ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ��������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*        [lens]          ���������飬����/���������ʱ��ʾ blob �ĳ��ȣ�
*                        ���ʱ��ʾʵ�ʻ�ȡ�Ķ�����/�ַ������ݳ��ȡ�
*        [blobs]         �ֽ������飬�����������/�ַ�����ʷֵ
*        [qualities]     ���������飬�������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goh_get_archived_blob_values(
                             golden_int32 handle,
                             golden_int32 id,
                             golden_int32 *count,
                             golden_int32 datetime1,
                             golden_int16 ms1,
                             golden_int32 datetime2,
                             golden_int16 ms2,
                             golden_int32 *datetimes,
                             golden_int16 *ms,
                             golden_int16 *lens,
                             golden_byte* const* blobs,
                             golden_int16 *qualities
                             );

/**
* ������goh_get_single_datetime_value
* ���ܣ���ȡ������ǩ��ĳ��ʱ���datetime��ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [mode]          ���ͣ����룬ȡֵ GOLDEN_NEXT��GOLDEN_PREVIOUS��GOLDEN_EXACT ֮һ��
*                        GOLDEN_NEXT Ѱ����һ����������ݣ�
*                        GOLDEN_PREVIOUS Ѱ����һ����������ݣ�
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*        [datetime]      ���ͣ�����/���������ʱ��ʾʱ��������
*                        ���ʱ��ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��ʾʱ������������ʱ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*                        ����������룬���ʱΪ 0��
*        [blob]          �ֽ������飬�����datetime��ʷֵ
*        [len]           �����ͣ�����/���������ʱ��ʾ blob �ĳ��ȣ�
*                        ���ʱ��ʾʵ�ʻ�ȡ��datetime���ݳ��ȡ�
*        [quality]       �����ͣ��������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_DATETIME �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_single_datetime_value(
                              golden_int32 handle,
                              golden_int32 id, 
                              golden_int32 mode, 
                              golden_int32 *datetime,
                              golden_int16 *ms, 
                              golden_byte *dtblob,
                              golden_int16 *dtlen,
                              golden_int16 *quality,
                              golden_int16 type = -1
                             );

/**
* ������goh_get_archived_datetime_values
* ���ܣ���ȡ������ǩ��һ��ʱ���ʱ��������ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*        [count]         ���ͣ�����/����������ʾ��Ҫ��ѯ��������
*                        �����ʾʵ�ʲ鵽��������
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ��������
*        [ms1]           �����ͣ����룬ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������
*        [datetime2]     ���ͣ�����,��ʾ����ʱ��������
*        [ms2]           �����ͣ����룬ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������
*        [datetimes]     �������飬�������ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ��������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*        [dtlens]          ���������飬����/���������ʱ��ʾ blob �ĳ��ȣ�
*                        ���ʱ��ʾʵ�ʻ�ȡ���������ݳ��ȡ�
*        [dtvalues]         �ֽ������飬�����������ʷֵ
*        [qualities]     ���������飬�������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [type]          �����ͣ����룬��yyyy-mm-dd hh:mm:ss.000����typeΪ1�� ͬ��Ĭ�������ʽҲΪ ��yyyy-mm-dd hh:mm:ss.000��
*                       ��yyyy/mm/dd hh:mm:ss.000����typeΪ2 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_DATETIME �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goh_get_archived_datetime_values(
                                golden_int32 handle,
                                golden_int32 id,
                                golden_int32 *count,
                                golden_int32 datetime1,
                                golden_int16 ms1,
                                golden_int32 datetime2,
                                golden_int16 ms2,
                                golden_int32 *datetimes,
                                golden_int16 *ms,
                                golden_int16 *lens,
                                golden_byte* const* blobs,
                                golden_int16 *qualities,
                                golden_int16 type = -1
                                );


/**
* ������goh_put_archived_datetime_values
* ���ܣ�д��������ǩ������ʱ������ʷ�洢����
* ������
*        [handle]        ���Ӿ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ ids��datetimes��ms��dtlens��dtvalues��qualities��errors �ĳ��ȣ�
*                        ����ʷֵ���������ʱ����ʵ��д�����ֵ����
*        [ids]           �������飬���룬��ǩ���ʶ
*        [datetimes]     �������飬���룬��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬���룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾ��Ӧ����ʷ��ֵʱ����룻������ԡ�
*        [dtvalues]      �ֽ���ָ�����飬���룬ʵʱʱ����ֵ
*        [dtlens]        ���������飬���룬ʱ����ֵ���ȣ�
*                        ��ʾ��Ӧ�� dtvalues ָ��ָ��Ļ��������ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [qualities]     ���������飬���룬��ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]        �޷����������飬�����д����ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��dtlens��dtvalues��qualities��errors �ĳ����� count һ�£�
*        ���ӿڽ�����������Ϊ GOLDEN_DATETIME �ı�ǩ����Ч��
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/

GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_archived_datetime_values(
                            golden_int32 handle, 
                            golden_int32 *count, 
                            const golden_int32 *ids,
                            const golden_int32 *datetimes, 
                            const golden_int16 *ms, 
                            const golden_byte* const* dtvalues, 
                            const golden_int16 *dtlens, 
                            const golden_int16 *qualities, 
                            golden_error* errors
                            );

/**
* ������goh_summary
* ���ܣ���ȡ������ǩ��һ��ʱ���ڵ�ͳ��ֵ��
* ������
*        [handle]            ���Ӿ��
*        [id]                ���ͣ����룬��ǩ���ʶ
*        [datetime1]         ���ͣ�����/���������ʱ��ʾ��ʼʱ��������
*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
*                            ���ʱ�������ֵ��ʱ��������
*        [ms1]               �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ��ʼʱ���Ӧ�ĺ��룬���ʱ��ʾ���ֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [datetime2]         ���ͣ�����/���������ʱ��ʾ����ʱ��������
*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
*                            ���ʱ������Сֵ��ʱ��������
*        [ms2]               �����ͣ���� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ����ʱ���Ӧ�ĺ��룬���ʱ��ʾ��Сֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [max_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ������ֵ��
*        [min_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ���С��ֵ��
*        [total_value]       ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
*        [calc_avg]          ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
*        [power_avg]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_summary(
            golden_int32 handle,
            golden_int32 id,
            golden_int32 *datetime1, 
            golden_int16 *ms1, 
            golden_int32 *datetime2, 
            golden_int16 *ms2, 
            golden_float64 *max_value,
            golden_float64 *min_value, 
            golden_float64 *total_value, 
            golden_float64 *calc_avg, 
            golden_float64 *power_avg
            );

///**
//* ������goh_summary_ex
//* ���ܣ���ȡ������ǩ��һ��ʱ���ڵ�ͳ��ֵ���Լ����ڼ���ͳ��ֵ�����ݸ�����
//* ������
//*        [handle]            ���Ӿ��
//*        [id]                ���ͣ����룬��ǩ���ʶ
//*        [datetime1]         ���ͣ�����/���������ʱ��ʾ��ʼʱ��������
//*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
//*                            ���ʱ�������ֵ��ʱ��������
//*        [ms1]               �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
//*                            ��ʾ��ʼʱ���Ӧ�ĺ��룬���ʱ��ʾ���ֵ��ʱ���������������ԣ�����ֵΪ 0
//*        [datetime2]         ���ͣ�����/���������ʱ��ʾ����ʱ��������
//*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
//*                            ���ʱ������Сֵ��ʱ��������
//*        [ms2]               �����ͣ���� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
//*                            ��ʾ����ʱ���Ӧ�ĺ��룬���ʱ��ʾ��Сֵ��ʱ���������������ԣ�����ֵΪ 0
//*        [max_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ������ֵ��
//*        [min_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ���С��ֵ��
//*        [total_value]       ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
//*        [calc_avg]          ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
//*        [power_avg]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
//*        [count]             ���ͣ��������ʾͳ��ʱ��������ڼ���ͳ��ֵ�����ݸ�����
//* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
//*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
//*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
//*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
//*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
//*/
//GOLDENAPI
//golden_error
//GOLDENAPI_CALLRULE
//goh_summary_ex(
//golden_int32 handle,
//golden_int32 id,
//golden_int32 *datetime1,
//golden_int16 *ms1,
//golden_int32 *datetime2,
//golden_int16 *ms2,
//golden_float64 *max_value,
//golden_float64 *min_value,
//golden_float64 *total_value,
//golden_float64 *calc_avg,
//golden_float64 *power_avg,
//golden_int32 *count
//);
/**
* ������goh_summary_ex
* ���ܣ���ȡ������ǩ��һ��ʱ���ڵ�ͳ��ֵ���Լ����ڼ���ͳ��ֵ�����ݸ�����
* ������
*        [handle]            ���Ӿ��
*        [id]                ���ͣ����룬��ǩ���ʶ
*        [datetime1]         ���ͣ�����/���������ʱ��ʾ��ʼʱ��������
*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
*                            ���ʱ�������ֵ��ʱ��������
*        [ms1]               �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ��ʼʱ���Ӧ�ĺ��룬���ʱ��ʾ���ֵ��ʱ���������������ԣ�����ֵΪ 0
*        [datetime2]         ���ͣ�����/���������ʱ��ʾ����ʱ��������
*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
*                            ���ʱ������Сֵ��ʱ��������
*        [ms2]               �����ͣ���� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ����ʱ���Ӧ�ĺ��룬���ʱ��ʾ��Сֵ��ʱ���������������ԣ�����ֵΪ 0
*        [max_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ������ֵ��
*        [min_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ���С��ֵ��
*        [total_value]       ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
*        [calc_avg]          ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
*        [power_avg]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
*        [count]             ���ͣ��������ʾͳ��ʱ��������ڼ���ͳ��ֵ�����ݸ�����
* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goh_summary_ex(
golden_int32 handle,
golden_int32 id,
golden_int32 *datetime1,
golden_int16 *ms1,
golden_int32 *datetime2,
golden_int16 *ms2,
golden_float64 *max_value,
golden_float64 *min_value,
golden_float64 *total_value,
golden_float64 *calc_avg,
golden_float64 *power_avg,
golden_int32 *count
);
/**
* ������goh_summary_in_batches
* ���ܣ�������ȡ��һ��ǩ��һ��ʱ���ڵ�ͳ��ֵ
* ������
*        [handle]            ���Ӿ��
*        [id]                ���ͣ����룬��ǩ���ʶ
*        [count]             ���Σ�����/���������ʱ��ʾ datatimes1��ms1��datatimes2��ms2��
*                            max_values��min_values��total_values��calc_avgs��power_avgs��errors �ĳ��ȣ�
*                            ���ֶεĸ��������ʱ��ʾ�ɹ�ȡ��ͳ��ֵ�ķֶθ�����
*        [interval]          64 λ���ͣ����룬�ֶ�ʱ��������λΪ���롣
*                            ���Ϊ����㣬����ʱ��������1���룬���Ϊ�뼶�㣬��������1000���롣
*        [datetimes1]        �������飬����/���������ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
*                            ���ʱ���ظ����ֶζ�Ӧ�����ֵ��ʱ��������
*        [ms1]               ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��һ��Ԫ�ر�ʾ��ʼʱ���Ӧ�ĺ��룬
*                            ���ʱ���ظ����ֶζ�Ӧ�����ֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [datetimes2]        �������飬����/���������ʱ��һ��Ԫ�ر�ʾ����ʱ��������
*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
*                            ���ʱ���ظ����ֶζ�Ӧ����Сֵ��ʱ��������
*        [ms2]               ���������飬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��һ��Ԫ�ر�ʾ����ʱ���Ӧ�ĺ��룬
*                            ���ʱ���ظ����ֶζ�Ӧ����Сֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [max_values]        ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ������ֵ��
*        [min_values]        ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ���С��ֵ��
*        [total_values]      ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
*        [calc_avgs]         ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
*        [power_avgs]        ˫���ȸ��������飬�������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
*        [errors]            �޷����������飬�������ʾ�����ֶ�ȡ��ͳ��ֵ�ķ���ֵ��
* ��ע���� datetimes1[0]��ms1[0] ��ʾ��ʱ����Դ��� datetimes2[0]��ms2[0] ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_summary_in_batches(
                       golden_int32 handle,
                       golden_int32 id, 
                       golden_int32 *count, 
                       golden_int64 interval,
                       golden_int32 *datetimes1,
                       golden_int16 *ms1, 
                       golden_int32 *datetimes2, 
                       golden_int16 *ms2,
                       golden_float64 *max_values, 
                       golden_float64 *min_values,
                       golden_float64 *total_values, 
                       golden_float64 *calc_avgs, 
                       golden_float64 *power_avgs,
                       golden_error *errors
                       );

/**
* ������goh_get_plot_values
* ���ܣ���ȡ������ǩ��һ��ʱ�������ڻ�ͼ����ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [interval]      ���ͣ����룬ʱ��������������λΪ����
*                        һ���ʹ�û�ͼ�ĺ���(ʱ����)������Ļ��������
*                        �ù��ܽ���ʼ������ʱ��ȷ�Ϊ interval �����䣬
*                        ������ÿ������ĵ�һ�������һ����ֵ��������С��ֵ��һ���쳣��ֵ��
*                        �ʲ��� count �п�������屶�� interval ����ʷֵ������
*                        �����Ƽ������ count ������ interval ���屶��
*        [count]         ���ͣ�����/���������ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ����Ҫ��ȡ�������ʷֵ���������ʱ����ʵ�ʵõ�����ʷֵ������
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ����Դ����ʼ������ʱ�䡣
*        ��һ��Ԫ���γɵ�ʱ����Դ������һ��Ԫ���γɵ�ʱ�䣬
*        ��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_plot_values(
                    golden_int32 handle, 
                    golden_int32 id,
                    golden_int32 interval,
                    golden_int32 *count, 
                    golden_int32 *datetimes, 
                    golden_int16 *ms,
                    golden_float64 *values, 
                    golden_int64 *states,
                    golden_int16 *qualities
                    );

/**
* ������goh_get_cross_section_values
* ���ܣ���ȡ������ǩ����ĳһʱ�����ʷ��������
* ������
*        [handle]        ���Ӿ��
*        [ids]           �������飬���룬��ǩ���ʶ�б�
*        [mode]          ���ͣ����룬ȡֵ GOLDEN_NEXT��GOLDEN_PREVIOUS��GOLDEN_EXACT��GOLDEN_INTER ֮һ��
*                        GOLDEN_NEXT Ѱ����һ����������ݣ�
*                        GOLDEN_PREVIOUS Ѱ����һ����������ݣ�
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*                        GOLDEN_INTER ȡָ��ʱ����ڲ�ֵ���ݡ�
*        [count]         ���ͣ����룬��ʾ ids��datetimes��ms��values��states��qualities �ĳ��ȣ�����ǩ�������
*        [datatimes]     �������飬����/���������ʱ��ʾ��Ӧ��ǩ�����ʷ��ֵʱ��������
*                        ���ʱ��ʾ���� mode ʵ��Ѱ�ҵ�����ֵʱ��������
*        [ms]            ���������飬����/���������ʱ�侫��Ϊ����ı�ǩ�㣬
*                        ����ʱ��ʾ��ʷ��ֵʱ��������������Ӧ�ĺ���ֵ��
*                        ���ʱ��ʾ���� mode ʵ��Ѱ�ҵ�����ֵʱ�������������������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]        �޷����������飬�������ȡ��ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_cross_section_values(
                             golden_int32 handle,
                             const golden_int32 *ids,
                             golden_int32 mode, 
                             golden_int32 count,
                             golden_int32 *datetimes, 
                             golden_int16 *ms, 
                             golden_float64 *values, 
                             golden_int64 *states, 
                             golden_int16 *qualities,
                             golden_error *errors
                             );

/**
* ������goh_subscribe_playback
* ���ܣ�����һ����ǩ�����ʷ���ݻط�
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/�������ǩ�������
*                    ����ʱ��ʾ ids��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ����ĵı�ǩ�����
*        [ids]       �������飬���룬��ǩ���ʶ�б�
*        [datetime1] ���ͣ����룬�ط�ʱ�����ʼʱ�䡣
*        [datetime2] ���ͣ����룬�ط�ʱ��ν���ʱ�䡣
*        [interval]  ���ͣ����룬ÿ���ν��յ�������֮���ʱ���ȣ���λ���롣
*        [callback]  goh_data_playback ���ͻص��ӿڣ����룬
*                    ͨ���ýӿڻ�ñ�ǩ��Ļط����ݡ�
*        [errors]    �޷����������飬�����
*                    �����Ƿ�ɹ����б��ο�golden_error.h
* ��ע���û��뱣֤ ids��errors �ĳ����� count һ�¡�
*        ���ڶ������ݻطŵ����Ӿ�������Ƕ����ģ������������������� api��
*        ���򷵻� GoE_OTHER_SDK_DOING ����
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_subscribe_playback(
                       golden_int32 handle,
                       golden_int32 *count,
                       const golden_int32 *ids,
                       golden_int32 datetime1,
                       golden_int32 datetime2,
                       golden_int32 interval,
                       goh_data_playback callback,
                       golden_error *errors
                       );

/**
* ������goh_stop_playback
* ���ܣ�ֹͣ��ʷ���ݻط�
* ������
*        [handle]    ���Ӿ��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_stop_playback(
                  golden_int32 handle
                  );

/**
* ������goh_get_archived_values_filt
* ���ܣ���ȡ������ǩ����һ��ʱ���ھ���������ɸѡ�����ʷ����ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [filter]        �ַ��������룬���������߼��������ɵĸ����������ʽ��
*                        ���Ȳ��ó��� GOLDEN_EQUATION_SIZE��Ϊ 0 �򲻽�������ɸѡ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ����Ҫ����ֵ���������ʱ����ʵ�ʵõ�����ֵ������
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ�洢ֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ�洢ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_archived_values_filt(
                             golden_int32 handle,
                             golden_int32 id,
                             const char *filter,
                             golden_int32 *count,
                             golden_int32 *datetimes,
                             golden_int16 *ms,
                             golden_float64 *values, 
                             golden_int64 *states,
                             golden_int16 *qualities
                             );

/**
* ������goh_get_interval_values_filt
* ���ܣ���ȡ������ǩ��ĳ��ʱ��֮�󾭸�������ɸѡ��һ�������ĵȼ���ڲ�ֵ�滻����ʷ��ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [filter]        �ַ��������룬���������߼��������ɵĸ����������ʽ��
*                        ���Ȳ��ó��� GOLDEN_EQUATION_SIZE������Ϊ 0 �򲻽�������ɸѡ��
*        [interval]      ���ͣ����룬��ֵʱ��������λΪ����
*        [count]         ���ͣ����룬��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ����Ҫ�Ĳ�ֵ������
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�����ڱ�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_interval_values_filt(
                             golden_int32 handle,
                             golden_int32 id,
                             const char *filter,
                             golden_int64 interval,
                             golden_int32 count,
                             golden_int32 *datetimes,
                             golden_int16 *ms, 
                             golden_float64 *values,
                             golden_int64 *states,
                             golden_int16 *qualities
                             );

/**
* ������goh_get_interpo_values_filt
* ���ܣ���ȡ������ǩ��һ��ʱ���ھ���������ɸѡ��ĵȼ����ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [filter]        �ַ��������룬���������߼��������ɵĸ����������ʽ��
*                        ���Ȳ��ó��� GOLDEN_EQUATION_SIZE������Ϊ 0 �򲻽�������ɸѡ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ datetimes��ms��values��states��qualities �ĳ��ȣ�
*                        ����Ҫ�Ĳ�ֵ���������ʱ����ʵ�ʵõ��Ĳ�ֵ����
*        [datetimes]     �������飬����/�����
*                        ����ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                        ���һ��Ԫ�ر�ʾ����ʱ�����������Ϊ 0����ʾֱ�����ݵ����ʱ�䣻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��һ��Ԫ�ر�ʾ��ʼʱ����룬
*                        ���һ��Ԫ�ر�ʾ����ʱ����룻
*                        ���ʱ��ʾ��Ӧ����ʷ��ֵʱ����롣
*                        ����������룬���ʱΪ 0��
*        [values]        ˫���ȸ��������飬�������������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [states]        64 λ�������飬�����������ʷ��ֵ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����Ӧ����ʷ��ֵ������Ϊ 0
*        [qualities]     ���������飬�������ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע���û��뱣֤ datetimes��ms��values��states��qualities �ĳ����� count һ�£�
*        ������ʱ��datetimes��ms ������Ӧ��һ��Ԫ�أ���һ��Ԫ���γɵ�ʱ�����
*        �������һ��Ԫ���γɵ�ʱ�䣬��ʱ��һ��Ԫ�ر�ʾ����ʱ�䣬
*        ���һ��Ԫ�ر�ʾ��ʼʱ�䡣
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_interpo_values_filt(
                            golden_int32 handle,
                            golden_int32 id,
                            const char *filter,
                            golden_int32 *count, 
                            golden_int32 *datetimes, 
                            golden_int16 *ms, 
                            golden_float64 *values, 
                            golden_int64 *states,
                            golden_int16 *qualities
                            );

/**
* ������goh_summary_filt
* ���ܣ���ȡ������ǩ��һ��ʱ���ھ���������ɸѡ���ͳ��ֵ
* ������
*        [handle]            ���Ӿ��
*        [id]                ���ͣ����룬��ǩ���ʶ
*        [filter]            �ַ��������룬���������߼��������ɵĸ����������ʽ��
*                            ���Ȳ��ó��� GOLDEN_EQUATION_SIZE������Ϊ 0 �򲻽�������ɸѡ��
*        [datetime1]         ���ͣ�����/���������ʱ��ʾ��ʼʱ��������
*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
*                            ���ʱ�������ֵ��ʱ��������
*        [ms1]               �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ��ʼʱ���Ӧ�ĺ��룬���ʱ��ʾ���ֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [datetime2]         ���ͣ�����/���������ʱ��ʾ����ʱ��������
*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
*                            ���ʱ������Сֵ��ʱ��������
*        [ms2]               �����ͣ���� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ����ʱ���Ӧ�ĺ��룬���ʱ��ʾ��Сֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [max_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ������ֵ��
*        [min_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ���С��ֵ��
*        [total_value]       ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
*        [calc_avg]          ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
*        [power_avg]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_summary_filt(
                 golden_int32 handle,
                 golden_int32 id,
                 const char *filter,
                 golden_int32 *datetime1, 
                 golden_int16 *ms1, 
                 golden_int32 *datetime2, 
                 golden_int16 *ms2, 
                 golden_float64 *max_value, 
                 golden_float64 *min_value, 
                 golden_float64 *total_value,
                 golden_float64 *calc_avg, 
                 golden_float64 *power_avg
                 );

/**
* ������goh_summary_filt_ex
* ���ܣ���ȡ������ǩ��һ��ʱ���ھ���������ɸѡ���ͳ��ֵ���Լ�����ͳ�Ƶ����ݸ���
* ������
*        [handle]            ���Ӿ��
*        [id]                ���ͣ����룬��ǩ���ʶ
*        [filter]            �ַ��������룬���������߼��������ɵĸ����������ʽ��
*                            ���Ȳ��ó��� GOLDEN_EQUATION_SIZE������Ϊ 0 �򲻽�������ɸѡ��
*        [datetime1]         ���ͣ�����/���������ʱ��ʾ��ʼʱ��������
*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
*                            ���ʱ�������ֵ��ʱ��������
*        [ms1]               �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ��ʼʱ���Ӧ�ĺ��룬���ʱ��ʾ���ֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [datetime2]         ���ͣ�����/���������ʱ��ʾ����ʱ��������
*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
*                            ���ʱ������Сֵ��ʱ��������
*        [ms2]               �����ͣ���� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��ʾ����ʱ���Ӧ�ĺ��룬���ʱ��ʾ��Сֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [max_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ������ֵ��
*        [min_value]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ���С��ֵ��
*        [total_value]       ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
*        [calc_avg]          ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
*        [power_avg]         ˫���ȸ����ͣ��������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
*        [count]             ���ͣ��������ʾͳ��ʱ��������ڼ���ͳ��ֵ�����ݸ�����
* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_summary_filt_ex(
	                golden_int32 handle,
	                golden_int32 id,
	                const char *filter,
	                golden_int32 *datetime1, 
	                golden_int16 *ms1, 
	                golden_int32 *datetime2, 
	                golden_int16 *ms2, 
	                golden_float64 *max_value, 
	                golden_float64 *min_value, 
	                golden_float64 *total_value,
	                golden_float64 *calc_avg, 
	                golden_float64 *power_avg,
	                golden_int32 *count
	                );

/**
* ������goh_summary_filt_in_batches
* ���ܣ�������ȡ��һ��ǩ��һ��ʱ���ھ���������ɸѡ���ͳ��ֵ
* ������
*        [handle]            ���Ӿ��
*        [id]                ���ͣ����룬��ǩ���ʶ
*        [filter]            �ַ��������룬���������߼��������ɵĸ����������ʽ��
*                            ���Ȳ��ó��� GOLDEN_EQUATION_SIZE������Ϊ 0 �򲻽�������ɸѡ��
*        [count]             ���Σ�����/���������ʱ��ʾ datatimes1��ms1��datatimes2��ms2��
*                            max_values��min_values��total_values��calc_avgs��power_avgs��errors �ĳ��ȣ�
*                            ���ֶεĸ��������ʱ��ʾ�ɹ�ȡ��ͳ��ֵ�ķֶθ�����
*        [interval]          64 λ���ͣ����룬�ֶ�ʱ��������λΪ���롣
*        [datetimes1]        �������飬����/���������ʱ��һ��Ԫ�ر�ʾ��ʼʱ��������
*                            ���Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ����ͳ�ơ�
*                            ���ʱ���ظ����ֶζ�Ӧ�����ֵ��ʱ��������
*        [ms1]               ���������飬����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��һ��Ԫ�ر�ʾ��ʼʱ���Ӧ�ĺ��룬
*                            ���ʱ���ظ����ֶζ�Ӧ�����ֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [datetimes2]        �������飬����/���������ʱ��һ��Ԫ�ر�ʾ����ʱ��������
*                            ���Ϊ 0����ʾͳ�Ƶ��浵�����ʱ�������Ϊֹ��
*                            ���ʱ���ظ����ֶζ�Ӧ����Сֵ��ʱ��������
*        [ms2]               ���������飬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                            ��һ��Ԫ�ر�ʾ����ʱ���Ӧ�ĺ��룬
*                            ���ʱ���ظ����ֶζ�Ӧ����Сֵ��ʱ���������������ԣ�����ֵΪ 0 
*        [max_values]        ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ������ֵ��
*        [min_values]        ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ���С��ֵ��
*        [total_values]      ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ��ۼ�ֵ������ĵ�λΪ��ǩ��Ĺ��̵�λ��
*        [calc_avgs]         ˫���ȸ��������飬�������ʾͳ��ʱ����ڵ�����ƽ��ֵ��
*        [power_avgs]        ˫���ȸ��������飬�������ʾͳ��ʱ����ڵļ�Ȩƽ��ֵ��
*        [errors]            �޷����������飬�������ʾ�����ֶ�ȡ��ͳ��ֵ�ķ���ֵ��
* ��ע���� datetimes1[0]��ms1[0] ��ʾ��ʱ����Դ��� datetimes2[0]��ms2[0] ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*        �����������ֵ����Сֵ��ʱ�����ֵΪ 0��
*        ����������ۼ�ֵ�ͼ�Ȩƽ��ֵ�����Ч������ͳ�ƽ����Ч��
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_summary_filt_in_batches(
                            golden_int32 handle,
                            golden_int32 id, 
                            const char *filter,
                            golden_int32 *count, 
                            golden_int64 interval,
                            golden_int32 *datetimes1,
                            golden_int16 *ms1, 
                            golden_int32 *datetimes2, 
                            golden_int16 *ms2,
                            golden_float64 *max_values, 
                            golden_float64 *min_values,
                            golden_float64 *total_values, 
                            golden_float64 *calc_avgs, 
                            golden_float64 *power_avgs,
                            golden_error *errors
                            );

/**
* ������goh_update_value
* ���ܣ��޸ĵ�����ǩ��ĳһʱ�����ʷ�洢ֵ.
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime]      ���ͣ����룬ʱ������
*        [ms]            �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������������ԡ�
*        [value]         ˫���ȸ����������룬��������ʷ��ֵ
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬����µ���ʷֵ���������
*        [state]         64 λ���������룬������ʷ��ֵ��
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬����µ���ʷֵ���������
*        [quality]       �����ͣ����룬�µ���ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_update_value(
                 golden_int32 handle,
                 golden_int32 id, 
                 golden_int32 datetime, 
                 golden_int16 ms, 
                 golden_float64 value, 
                 golden_int64 state,
                 golden_int16 quality
                 );

/**
* ������goh_update_coor_value
* ���ܣ��޸ĵ�����ǩ��ĳһʱ�����ʷ�洢ֵ.
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime]      ���ͣ����룬ʱ������
*        [ms]            �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������������ԡ�
*        [x]             �����ȸ����ͣ����룬�µĺ�������ʷ��ֵ
*        [y]             �����ȸ����ͣ����룬�µ���������ʷ��ֵ
*        [quality]       �����ͣ����룬�µ���ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿڽ�����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_update_coor_value(
                      golden_int32 handle,
                      golden_int32 id,
                      golden_int32 datetime,
                      golden_int16 ms,
                      golden_float32 x,
                      golden_float32 y,
                      golden_int16 quality
                      );


/**
* ������goh_remove_value
* ���ܣ�ɾ��������ǩ��ĳ��ʱ�����ʷ�洢ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime]      ���ͣ����룬ʱ������
*        [ms]            �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������������ԡ�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_remove_value(
                 golden_int32 handle,
                 golden_int32 id,
                 golden_int32 datetime,
                 golden_int16 ms
                 );

/**
* ������goh_remove_values
* ���ܣ�ɾ��������ǩ��һ��ʱ���ڵ���ʷ�洢ֵ
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ�����������Ϊ 0����ʾ�Ӵ浵������ʱ������ݿ�ʼ��ȡ
*        [ms1]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ��ʼʱ���Ӧ�ĺ��룻�������
*        [datetime2]     ���ͣ����룬��ʾ����ʱ�����������Ϊ 0����ʾ��ȡֱ���浵�����ݵ����ʱ��
*        [ms2]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ����ʱ���Ӧ�ĺ��룻�������
*        [count]         ���Σ��������ʾɾ������ʷֵ����
* ��ע���� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_remove_values(
                  golden_int32 handle,
                  golden_int32 id,
                  golden_int32 datetime1, 
                  golden_int16 ms1,
                  golden_int32 datetime2, 
                  golden_int16 ms2,
                  golden_int32 *count
                  );


/**
* ������goh_put_single_value
* ���ܣ�д�뵥����ǩ����ĳһʱ�����ʷ���ݡ�
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime]      ���ͣ����룬ʱ������
*        [ms]            �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������������ԡ�
*        [value]         ˫���ȸ����������룬��������ʷ��ֵ
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬�����ʷֵ���������
*        [state]         64 λ���������룬������ʷ��ֵ��
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬�����ʷֵ���������
*        [quality]       �����ͣ����룬��ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_single_value(
                     golden_int32 handle, 
                     golden_int32 id,
                     golden_int32 datetime, 
                     golden_int16 ms,
                     golden_float64 value, 
                     golden_int64 state,
                     golden_int16 quality
                     );

/**
* ������goh_put_single_coor_value
* ���ܣ�д�뵥����ǩ����ĳһʱ�����������ʷ���ݡ�
* ������
*        [handle]              ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [datetime]      ���ͣ����룬ʱ������
*        [ms]            �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������������ԡ�
*        [x]             �����ȸ����ͣ����룬��������ʷ��ֵ
*        [y]             �����ȸ����ͣ����룬��������ʷ��ֵ
*        [quality]       �����ͣ����룬��ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_single_coor_value(
                          golden_int32 handle, 
                          golden_int32 id, 
                          golden_int32 datetime, 
                          golden_int16 ms, 
                          golden_float32 x, 
                          golden_float32 y, 
                          golden_int16 quality
                          );

/**
* ������goh_put_single_blob_value
* ���ܣ�д�뵥��������/�ַ�����ǩ����ĳһʱ�����ʷ����
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ����룬��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ����룬��ʷ��ֵʱ�䣬
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [blob]      �ֽ������飬���룬��ʷ������/�ַ�����ֵ
*        [len]       �����ͣ����룬������/�ַ�����ֵ���ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [quality]   �����ͣ����룬��ʷ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_single_blob_value(
                          golden_int32 handle,
                          golden_int32 id,
                          golden_int32 datetime, 
                          golden_int16 ms, 
                          const golden_byte *blob,
                          golden_int16 len,
                          golden_int16 quality
                          );

/**
* ������goh_put_archived_values
* ���ܣ�д��������ǩ��������ʷ�洢����
* ������
*        [handle]        ���Ӿ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ ids��datetimes��ms��values��states��qualities��errors �ĳ��ȣ�
*                        ����ʷֵ���������ʱ����ʵ��д�����ֵ����
*        [ids]           �������飬���룬��ǩ���ʶ��ͬһ����ǩ���ʶ���Գ��ֶ�Σ�
*                        �����ǵ�ʱ��������ǵ����ġ�
*        [datetimes]     �������飬���룬��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬���룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾ��Ӧ����ʷ��ֵʱ����룻������ԡ�
*        [values]        ˫���ȸ��������飬���룬��������ʷ��ֵ�б�
*                        ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬��ʾ��Ӧ����ʷ�洢ֵ���������
*        [states]        64 λ�������飬���룬������ʷ��ֵ�б�
*                        ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                        GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬��ʾ��Ӧ����ʷ�洢ֵ���������
*        [qualities]     ���������飬���룬��ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]        �޷����������飬�����д����ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��values��states��qualities��errors �ĳ����� count һ�£�
*        ���ӿڶ���������Ϊ GOLDEN_COOR��GOLDEN_BLOB��GOLDEN_STRING �ı�ǩ����Ч��
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_archived_values(
                        golden_int32 handle, 
                        golden_int32 *count, 
                        const golden_int32 *ids, 
                        const golden_int32 *datetimes,
                        const golden_int16 *ms, 
                        const golden_float64 *values,
                        const golden_int64 *states,
                        const golden_int16 *qualities,
                        golden_error *errors
                        );

/**
* ������goh_put_archived_coor_values
* ���ܣ�д��������ǩ��������������ʷ�洢����
* ������
*        [handle]        ���Ӿ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ ids��datetimes��ms��x��y��qualities��errors �ĳ��ȣ�
*                        ����ʷֵ���������ʱ����ʵ��д�����ֵ����
*        [ids]           �������飬���룬��ǩ���ʶ
*        [datetimes]     �������飬���룬��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬���룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾ��Ӧ����ʷ��ֵʱ����룻������ԡ�
*        [x]             �����ȸ��������飬���룬�����ͺ�������ʷ��ֵ�б�
*        [y]             �����ȸ��������飬���룬��������������ʷ��ֵ�б�
*        [qualities]     ���������飬���룬��ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]        �޷����������飬�����д����ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��x��y��qualities��errors �ĳ����� count һ�£�
*        ���ӿڽ�����������Ϊ GOLDEN_COOR �ı�ǩ����Ч��
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_archived_coor_values(
                             golden_int32 handle, 
                             golden_int32 *count, 
                             const golden_int32 *ids, 
                             const golden_int32 *datetimes, 
                             const golden_int16 *ms, 
                             const golden_float32 *x, 
                             const golden_float32 *y, 
                             const golden_int16 *qualities,
                             golden_error *errors
                             );

/**
* ������goh_put_single_datetime_value
* ���ܣ�д�뵥��datetime��ǩ����ĳһʱ�����ʷ����
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ����룬��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ����룬��ʷ��ֵʱ�䣬
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [blob]      �ֽ������飬���룬��ʷdatetime��ֵ
*        [len]       �����ͣ����룬datetime��ֵ���ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [quality]   �����ͣ����룬��ʷ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
* ��ע�����ӿ�ֻ����������Ϊ GOLDEN_DATETIME �ı�ǩ����Ч��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_single_datetime_value(
                              golden_int32 handle,
                              golden_int32 id,
                              golden_int32 datetime, 
                              golden_int16 ms, 
                              const golden_byte *blob,
                              golden_int16 len,
                              golden_int16 quality
                              );



/**
* ������goh_put_archived_blob_values
* ���ܣ�д��������ǩ�������ַ�������ʷ�洢����
* ������
*        [handle]        ���Ӿ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ ids��datetimes��ms��lens��blobs��qualities��errors �ĳ��ȣ�
*                        ����ʷֵ���������ʱ����ʵ��д�����ֵ����
*        [ids]           �������飬���룬��ǩ���ʶ
*        [datetimes]     �������飬���룬��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬���룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾ��Ӧ����ʷ��ֵʱ����룻������ԡ�
*        [blobs]         �ֽ���ָ�����飬���룬ʵʱ������/�ַ�����ֵ
*        [lens]          ���������飬���룬������/�ַ�����ֵ���ȣ�
*                        ��ʾ��Ӧ�� blobs ָ��ָ��Ļ��������ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [qualities]     ���������飬���룬��ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]        �޷����������飬�����д����ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��lens��blobs��qualities��errors �ĳ����� count һ�£�
*        ���ӿڽ�����������Ϊ GOLDEN_STRING��GOLDEN_BLOB �ı�ǩ����Ч��
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/

GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_archived_blob_values(
                            golden_int32 handle, 
                            golden_int32 *count, 
                            const golden_int32 *ids,
                            const golden_int32 *datetimes, 
                            const golden_int16 *ms, 
                            const golden_byte* const* blobs, 
                            const golden_int16 *lens, 
                            const golden_int16 *qualities, 
                            golden_error* errors
                            );

/**
* ������goh_flush_archived_values
* ���ܣ�����ǩ��δд���Ĳ���ʷ����ҳд��浵�ļ��С�
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ��
*        [count]         ���ͣ����������ҳ�����ݸ�����
* ��ע������ʷ����ҳд������Զ�д��浵�ļ��У���������ʷ����ҳҲ��д���ļ���
*      ������һ��ʱ���ӳ٣��ڴ��ڼ�˶����ݿ��ܲ�ѯ������Ϊ�˼�ʱ��������ʷ�Ľ����
*      Ӧ�ڽ�������ʷ����ñ��ӿڡ�
*      count ������Ϊ��ָ�룬��Ӧ����Ϣ�����ٷ��ء�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_flush_archived_values(
                          golden_int32 handle, 
                          golden_int32 id, 
                          golden_int32 *count
                          );


/**
* ������goh_get_single_named_type_value
* ���ܣ���ȡ�����Զ������ͱ�ǩ��ĳ��ʱ�����ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*        [mode]          ���ͣ����룬ȡֵ GOLDEN_NEXT��GOLDEN_PREVIOUS��GOLDEN_EXACT ֮һ��
*                        GOLDEN_NEXT Ѱ����һ����������ݣ�
*                        GOLDEN_PREVIOUS Ѱ����һ����������ݣ�
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*        [datetime]      ���ͣ�����/���������ʱ��ʾʱ��������
*                        ���ʱ��ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ�����/�������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ������ʱ��ʾʱ������������ʱ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*                        ����������룬���ʱΪ 0��
*        [object]        void���飬������Զ������ͱ�ǩ����ʷֵ
*        [length]        �����ͣ�����/���������ʱ��ʾ object �ĳ��ȣ�
*                        ���ʱ��ʾʵ�ʻ�ȡ���Զ������ͱ�ǩ�����ݳ��ȡ�
*        [quality]       �����ͣ��������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_get_single_named_type_value(
    golden_int32 handle,
    golden_int32 id, 
    golden_int32 mode, 
    golden_int32 *datetime,
    golden_int16 *ms, 
    void *object,
    golden_int16 *length,
    golden_int16 *quality
    );

/**
* ������goh_get_archived_named_type_values
* ���ܣ�������ȡ�Զ������ͱ�ǩ�����ʷ����
* ������
*        [handle]        ���Ӿ��
*        [id]            ���ͣ����룬��ǩ���ʶ
*                        GOLDEN_EXACT ȡָ��ʱ������ݣ����û���򷵻ش��� GoE_DATA_NOT_FOUND��
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ��������
*        [ms1]           �����ͣ����룬ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������
*        [datetime2]     ���ͣ�����,��ʾ����ʱ��������
*        [ms2]           �����ͣ����룬ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʱ���������
*        [length]        ���������飬���룬����ʱ��ʾ objects �ĳ��ȣ�
*        [count]         ���ͣ�����/����������ʾ��Ҫ��ѯ��������
*                        �����ʾʵ�ʲ鵽��������
*        [datetimes]     �������飬�������ʾʵ��ȡ�õ���ʷ��ֵ��Ӧ��ʱ��������
*        [ms]            �����ͣ��������� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾʵ��ȡ�õ���ʷ��ֵʱ���������
*        [objects]       void�������飬������Զ������ͱ�ǩ����ʷֵ
*        [qualities]     ���������飬�������ʷֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
goh_get_archived_named_type_values(
    golden_int32 handle,
    golden_int32 id,
    golden_int32 datetime1,
    golden_int16 ms1,
    golden_int32 datetime2,
    golden_int16 ms2,
    golden_int16 length,
    golden_int32 *count,
    golden_int32 *datetimes,
    golden_int16 *ms,
    void* const* objects,
    golden_int16 *qualities
    );

/**
* ������goh_put_single_named_type_value
* ���ܣ�д���Զ������ͱ�ǩ��ĵ�����ʷ�¼�
* ������
*        [handle]    ���Ӿ��
*        [id]        ���ͣ����룬��ǩ���ʶ
*        [datetime]  ���ͣ����룬��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        �����ͣ����룬��ʷ��ֵʱ�䣬
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬�����Ӧ�ĺ���ֵ���������
*        [object]    void���飬���룬��ʷ�Զ������ͱ�ǩ����ֵ
*        [length]    �����ͣ����룬�Զ������ͱ�ǩ����ֵ���ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [quality]   �����ͣ����룬��ʷ��ֵƷ�ʣ����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_single_named_type_value(
    golden_int32 handle,
    golden_int32 id,
    golden_int32 datetime, 
    golden_int16 ms, 
    const void *object,
    golden_int16 length,
    golden_int16 quality
    );

/**
* ������goh_put_archived_named_type_values
* ���ܣ�������д�Զ������ͱ�ǩ�����ʷ�¼�
* ������
*        [handle]        ���Ӿ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ ids��datetimes��ms��lens��blobs��qualities��errors �ĳ��ȣ�
*                        ����ʷֵ���������ʱ����ʵ��д�����ֵ����
*        [ids]           �������飬���룬��ǩ���ʶ
*        [datetimes]     �������飬���룬��ʾ��Ӧ����ʷ��ֵʱ��������
*        [ms]            ���������飬���룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬
*                        ��ʾ��Ӧ����ʷ��ֵʱ����룻������ԡ�
*        [objects]       void����ָ�����飬���룬�Զ������ͱ�ǩ����ֵ
*        [lengths]       ���������飬���룬�Զ������ͱ�ǩ����ֵ���ȣ�
*                        ��ʾ��Ӧ�� objects ָ��ָ��Ļ��������ȣ�����һ��ҳ��С���ݽ����ضϡ�
*        [qualities]     ���������飬���룬��ʷ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]        �޷����������飬�����д����ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��lens��objects��qualities��errors �ĳ����� count һ�£�
*        ��� datetimes��ms ��ʶ�������Ѿ����ڣ���ֵ�����滻��
*/

GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goh_put_archived_named_type_values(
      golden_int32 handle, 
      golden_int32 *count, 
      const golden_int32 *ids,
      const golden_int32 *datetimes, 
      const golden_int16 *ms, 
      const void* const* objects, 
      const golden_int16 *lengths, 
      const golden_int16 *qualities, 
      golden_error* errors
      );

/************************************ ����ʽ����ӿ� ************************************/



/**
* ������goe_compute_history
* ���ܣ�����������������ǩ����ʷ����
* ������
*        [handle]        ���Ӿ��
*        [count]         ���ͣ�����/�����
*                        ����ʱ��ʾ ids��errors �ĳ��ȣ�
*                        ����ǩ����������ʱ���سɹ���ʼ����ı�ǩ�����
*        [flag]          �����ͣ����룬��Ϊ 0 ��ʾ�������㣬ɾ��ʱ�䷶Χ���Ѿ�������ʷ���ݣ�
*                        Ϊ 0 ��ʾ���㣬����ʱ�䷶Χ���Ѿ�������ʷ���ݣ�����ͬʱ�̵ļ���ֵ��
*        [datetime1]     ���ͣ����룬��ʾ��ʼʱ��������
*        [ms1]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ��ʼʱ���Ӧ�ĺ��룻�������
*        [datetime2]     ���ͣ����룬��ʾ����ʱ�����������Ϊ 0����ʾ����ֱ���浵�����ݵ����ʱ��
*        [ms2]           �����ͣ����룬��� id ָ���ı�ǩ��ʱ�侫��Ϊ���룬��ʾ����ʱ���Ӧ�ĺ��룻�������
*        [ids]           �������飬���룬��ǩ���ʶ
*        [errors]        �޷����������飬�����������ʷ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��errors �ĳ����� count һ�£����ӿڽ��Դ��м�����չ���Եı�ǩ����Ч��
*        �� datetime1��ms1 ��ʾ��ʱ����Դ��� datetime2��ms2 ��ʾ��ʱ�䣬
*        ��ʱǰ�߱�ʾ����ʱ�䣬���߱�ʾ��ʼʱ�䡣
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goe_compute_history(
                    golden_int32 handle, 
                    golden_int32 *count,
                    golden_int16 flag,
                    golden_int32 datetime1, 
                    golden_int16 ms1, 
                    golden_int32 datetime2, 
                    golden_int16 ms2, 
                    const golden_int32 *ids, 
                    golden_error *errors
                    );

/**
* ������goe_get_equation_graph_count
* ���ܣ����ݱ�ǩ�� id ��ȡ���������ʽ��ֵ������
* ������
*      [handle]   ���Ӿ��
*      [id]       ���ͣ����룬��ǩ���ʶ
*      [flag]     ö�٣����룬��ȡ������ͼ�Ĺ�ϵ
*      [count]    ���ͣ����룬����ͼ��ֵ������
* ��ע����ֵ��Ϊ���ݽṹ���洢����ʽ�漰���ĸ���ǩ��ID�����丸ID��
*		����ο�goe_get_equation_graph_datas
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goe_get_equation_graph_count(
							golden_int32 handle,
							golden_int32 id, 
              GOLDEN_GRAPH_FLAG flag,
							golden_int32 *count
							);

/**
* ������goe_get_equation_graph_datas
* ���ܣ����ݱ�ǩ�� id ��ȡ���������ʽ��ֵ������
* ������
*      [handle]   ���Ӿ��
*      [id]       ���ͣ����룬��ǩ���ʶ
*      [flag]     ö�٣����룬��ȡ������ͼ�Ĺ�ϵ
*      [count]    ���ͣ����
                    ����ʱ����ʾ����ͼ��ֵ������
                    ���ʱ����ʾʵ�ʻ�ȡ��������ͼ��ֵ������
*      [graph]    �����GOLDE_GRAPH���ݽṹ������ͼ��ֵ����Ϣ
* ��ע����ֵ��Ϊ���ݽṹ���洢����ʽ�漰���ĸ���ǩ��ID�����丸ID��
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
goe_get_equation_graph_datas(
								golden_int32 handle,
								golden_int32 id, 
                GOLDEN_GRAPH_FLAG flag,
								golden_int32 *count,
								GOLDEN_GRAPH *graph 
								);


/************************************ ��ѯ��ǩ�����Խӿ� ************************************/

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_tags_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *tags,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_ms_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *ms,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_types_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *types,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_compdevs_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *compdevs,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_compmaxs_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *compmaxs,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_compmins_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *compmins,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_excdevs_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *excdevs,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_excmaxs_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *excmaxs,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_excmins_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *excmins,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_classofs_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_uint8 *classofs,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_tables_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_uint16 *tables,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_summarys_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *summarys,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_mirrors_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *mirrors,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_compress_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *compress,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_steps_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *steps,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_shutdowns_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *shutdowns,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_archives_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *archives,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_table_dot_tags_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *table_dot_tags,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_descs_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *descs,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_units_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *units,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_changers_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *changers,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_creators_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *creators,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_lowlimits_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *lowlimits,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_highlimits_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *highlimits,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_typicals_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *typicals,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_changedates_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *changedates,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_createdates_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *createdates,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_digits_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int16 *digits,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_compdevpercents_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *compdevpercents,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_excdevpercents_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *excdevpercents,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_sources_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *sources,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_scans_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *scans,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_instruments_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *instruments,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_location1s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *location1s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_location2s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *location2s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_location3s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *location3s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_location4s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *location4s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_location5s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *location5s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_userint1s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *userint1s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_userint2s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *userint2s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_userreal1s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *userreal1s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_userreal2s_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_float32 *userreal2s,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_equations_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  char* const *equations,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_triggers_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *triggers,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_timecopys_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_byte *timecopys,
  golden_error *errors
  );

GOLDENAPI
  golden_error
  GOLDENAPI_CALLRULE 
  gob_get_periods_prpperty(
  golden_int32 handle,
  golden_int32 *count,
  golden_int32 *ids,
  golden_int32 *periods,
  golden_error *errors
  );


/************************************ ��ѯ���ܼ�����Ϣ�ӿ� ************************************/

/**
* ������gop_get_perf_tags_count
* ���ܣ���ȡPerf������֧�ֵ����ܼ����������
* ������
*      [handle]   ���Ӿ��
*      [count]    ���ͣ��������ʾʵ�ʻ�ȡ����Perf������֧�ֵ����ܼ����������
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE 
gop_get_perf_tags_count(
  golden_int32 handle,
  int* count);


/**
* ������gop_get_perf_tags_info
* ���ܣ��������ܼ�����ID��ȡ��ص����ܼ�������Ϣ
* ������
*      [handle]   ���Ӿ��
*      [count]    ���ͣ����룬���
                    ����ʱ����ʾ��Ҫ��ȡ�����ܼ�������Ϣ��������Ҳ��ʾtags_info��errors�ȵĳ���
                    ���ʱ����ʾʵ�ʻ�ȡ�������ܼ�������Ϣ������
       [errors] �޷����������飬�������ȡ���ܼ�������Ϣ�ķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤����� tags_info��errors �Ŀռ��� count ���
*/
GOLDENAPI
golden_error 
  GOLDENAPI_CALLRULE 
  gop_get_perf_tags_info(
  golden_int32 handle, 
  golden_int32* count, 
  GOLDEN_PERF_TAG_INFO* tags_info, 
  golden_error* errors);


/**
* ������gop_get_perf_values
* ���ܣ�������ȡ���ܼ�����ĵ�ǰ������ֵ
* ������
*        [handle]    ���Ӿ��
*        [count]     ���ͣ�����/��������ܵ������
*                    ����ʱ��ʾ perf_ids��datetimes��ms��values��states��qualities��errors �ĳ��ȣ�
*                    ���ʱ��ʾ�ɹ���ȡʵʱֵ�����ܼ��������
*        [perf_ids]  �������飬���룬���ܼ������ʶ�б��ο�GOLDEN_PERF_TAG_ID
*        [datetimes] �������飬�����ʵʱ��ֵʱ���б�,
*                    ��ʾ����1970��1��1��08:00:00������
*        [ms]        ���������飬�����ʵʱ��ֵʱ���б�
*                    ����ʱ�侫��Ϊ����ı�ǩ�㣬������Ӧ�ĺ���ֵ������Ϊ 0
*        [values]    ˫���ȸ��������飬�����ʵʱ��������ֵ�б�
*                    ������������Ϊ GOLDEN_REAL16��GOLDEN_REAL32��GOLDEN_REAL64 �ı�ǩ�㣬������Ӧ�Ŀ���ֵ������Ϊ 0
*        [states]    64 λ�������飬�����ʵʱ������ֵ�б�
*                    ������������Ϊ GOLDEN_BOOL��GOLDEN_UINT8��GOLDEN_INT8��GOLDEN_CHAR��GOLDEN_UINT16��GOLDEN_INT16��
*                    GOLDEN_UINT32��GOLDEN_INT32��GOLDEN_INT64 �ı�ǩ�㣬������Ӧ�Ŀ���ֵ������Ϊ 0
*        [qualities] ���������飬�����ʵʱ��ֵƷ���б����ݿ�Ԥ�����Ʒ�ʲμ�ö�� GOLDEN_QUALITY 
*        [errors]    �޷����������飬�������ȡʵʱ���ݵķ���ֵ�б��ο�golden_error.h
* ��ע���û��뱣֤ ids��datetimes��ms��values��states��qualities��errors �ĳ����� count һ�¡�
*/
GOLDENAPI
golden_error 
GOLDENAPI_CALLRULE
  gop_get_perf_values(
  golden_int32 handle,
  golden_int32* count, 
  int* perf_ids, 
  int* datetimes, 
  golden_int16* ms, 
  golden_float64* values, 
  golden_int64* states, 
  golden_int16* qualities, 
  golden_error* errors);


#pragma region ת����������ģ��ͨ�Žӿ� add by yuanbo.sheng 2015.04.01
/**
* ������god_get_plugin_info_total_size
* ���ܣ���ȡ����ת�������Ϣ�ܳ���
* ������
*        [handle]    ���Ӿ��
*        [total_plugin_size]  �����Ϣ�ܳ��ȣ������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_get_plugin_info_total_size(golden_int32 handle, golden_int32& total_plugin_size);

/**
* ������god_get_plugin_info_array
* ���ܣ���ȡ����ת�������Ϣ
* ������
*        [handle]    ���Ӿ��
*        [plugin_info_array] �ַ��������������������total_plugin_size��
*        [total_plugin_size]  �����Ϣ�ܳ��ȣ������
 */
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_get_plugin_info_array(golden_int32 handle, char* plugin_info_array, golden_int32& total_plugin_size);

/**
* ������god_register_plugin
* ���ܣ�ע������Ϣ
* ������
*        [handle]    ���Ӿ��
*        [_plugin_info] �ַ��������������������plugin_size��
*        [_plugin_size]  �����Ϣ���ȣ�
*        [plugin_id] �����ţ������
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_register_plugin(golden_int32 handle, const char* _plugin_info, golden_int32 plugin_size, golden_int32& plugin_id);

/**
* ������god_unregister_plugin
* ���ܣ�ж�ز����Ϣ
* ������
*        [handle]    ���Ӿ��
*        [plugin_id] �����ţ�
 */
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_unregister_plugin(golden_int32 handle, golden_int32 plugin_id);

/*
 *
 * ���������������
 *
 * inputs:
 *     golden_int32 handle: ����ͨ�ž��
 *     golden_int32 plugin_id: ������
 * returns:
 *     0 �ɹ�  ���� ʧ��
 */
 
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
  god_start_configed_plugin_by_id(
  golden_int32 handle,
  golden_int32 plugin_id);

/*
 *
 * ����ת�����������������õĲ��
 * 
 *  inputs:
 *      golden_int32 handle: ����ͨ�ž�� 
 *  return:
 *      0 �ɹ�  ���� ʧ��
 */

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
  god_start_all_configed_plugins(
  golden_int32 handle);

/*
*
* ���������������
*
* inputs:
*     golden_int32 handle: ����ͨ�ž��
*     golden_int32 plugin_id: ������
* returns:
*     0 �ɹ�  ���� ʧ��
*/

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
  god_stop_configed_plugin_by_id(
  golden_int32 handle,
  golden_int32 plugin_id);

/*
 * 
 *  ֹͣ�������������õĲ��
 *  
 *  inputs:
 *      golden_int32 handle: ����ͨ�ž��
 *  return:
 *      0 �ɹ�  ���� ʧ��
 */
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
  god_stop_all_configed_plugins(
  golden_int32 handle);

/*
 *
 * �����������ò��������״̬
 *
 * inputs:
 *     golden_int32 handle: ����ͨ�ž��
 *     golden_int8  enable_status: �������״̬ ����ֵ�������Ϣ�ṹ��golden_output_plugin_info_t
 *     golden_int32 plugin_id: ������
 *     
 * returns:
 *     0 �ɹ�  ���� ʧ��
 */

GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
  god_switch_plugin_load_state(
  golden_int32 handle,
  golden_int32 plugin_id,
  golden_int32  enable_status);

/*
* ���ݲ����Ŷ�ȡָ�������Ϣ���ݳ���
*
* @input:
golden_int32 handle: ���ݿ����Ӿ��
golden_int32 plugin_id: ������
@output:
golden_int32 plugin_info_size�������Ϣ���ݳ���
@return:
0 �ɹ� ���� ʧ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_get_single_plugin_info_data_size (
golden_int32 handle,
golden_int32 plugin_id,
golden_int32& plugin_info_size);

/*
* ���ݲ����Ŷ�ȡָ�������Ϣ����
*
* @input:
    golden_int32 handle: ���ݿ����Ӿ��
    golden_int32 plugin_id: ������
  @output:
    char* plugin_info_data: �����Ϣ����
    golden_int32 plugin_info_size�������Ϣ���ݳ���
  @return:
    0 �ɹ� ���� ʧ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_get_single_plugin_info_data (
  golden_int32 handle,
  golden_int32 plugin_id,
  char* plugin_info_data,
  golden_int32& plugin_info_size
  );

/*
*  ���ݲ����Ÿ��²����Ϣ
   @input:
    golden_int32 handle: ���ݿ����Ӿ��
    golden_int32 plugin_id: ������
    const char* plugin_info_data : ��������
    golden_int32 plugin_info_size : �������ݳ���
   @output:
     ��
   @return:
     0 �ɹ� ���� ʧ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_set_single_plugin_info_data (
golden_int32 handle,
golden_int32 plugin_id,
const char* plugin_info_data,
golden_int32 plugin_info_size
);

/*
* ���ݲ����Ŷ�ȡָ������������ļ����ݳ���
*
* @input:
golden_int32 handle: ���ݿ����Ӿ��
golden_int32 plugin_id: ������
@output:
golden_int32 config_dize���������ݳ���
@return:
0 �ɹ� ���� ʧ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_get_download_plugin_config_data_size(
golden_int32 handle,
golden_int32 plugin_id,
golden_int32& config_size);

/*
* ���ݲ����Ŷ�ȡָ������������ļ�����
*
* @input:
    golden_int32 handle: ���ݿ����Ӿ��
    golden_int32 plugin_id: ������
  @output:
    char* config_data: ��������
    golden_int32 config_dize���������ݳ���
  @return:
    0 �ɹ� ���� ʧ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_download_plugin_config_data_by_id(
  golden_int32 handle,
  golden_int32 plugin_id,
  char* config_data,
  golden_int32& config_size
  );

/*
*  ���ݲ����Ÿ��²���������ļ�����

   @input:
    golden_int32 handle: ���ݿ����Ӿ��
    golden_int32 plugin_id: ������
    const char* config_data : ��������
    golden_int32 config_size : �������ݳ���
   @output:
     ��
   @return:
     0 �ɹ� ���� ʧ��
*/
GOLDENAPI
golden_error
GOLDENAPI_CALLRULE
god_upload_plugin_config_data_by_id(
  golden_int32 handle,
golden_int32 plugin_id,
const char* config_data,
golden_int32 config_size
);

#pragma endregion

#endif  // __GOLDEN_API_H__