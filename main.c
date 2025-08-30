/**
 * @file main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <direct.h>   /* For _mkdir */
#include <sys/stat.h> /* For stat */
#include <string.h>   /* For strrchr */
#include <io.h>       /* For _commit */
#include <cJSON.h>
/*********************
 *      DEFINES
 *********************/
#define PATH_FILE "data.json"
#define BUF_SIZE_NAME 64
#define BUF_SIZE_ADDRESS 256
#define SIZE_CONTACT_DATA 32
/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    e_AGE_18 = 0,
    e_AGE_19,
    e_AGE_20,
    e_AGE_21,
    e_AGE_22,
    e_AGE_23,
    e_AGE_24,
    e_AGE_25,
    e_AGE_26,
    e_AGE_27,
    e_AGE_28,
    e_AGE_29,
    e_AGE_30,
    e_AGE_31,
    e_AGE_32,
    e_AGE_33,
    e_AGE_34,
    e_AGE_35,
    e_AGE_36,
    e_AGE_37,
    e_AGE_38,
    e_AGE_39,
    e_AGE_40,
};
typedef uint8_t e_age_t;

typedef struct
{
    uint8_t age;      /* Age in years */
    e_age_t age_enum; /* Age as enum */
} st_person_t;

typedef struct
{
    char name[BUF_SIZE_NAME];
    char address[BUF_SIZE_ADDRESS];
    e_age_t age_enum;
    bool is_online;
} st_contact_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static long fs_get_file_size(const char *path);
static int fs_read(const char *path, long offset, size_t size, unsigned char *buffer);
static void process_contacts_json(const char* path_file, st_contact_t *fs_contact_data);
static void show_contact(st_contact_t *contact);

/**********************
 *  STATIC VARIABLES
 **********************/
static st_person_t fs_person_data[] = {
    {18, e_AGE_18},
    {19, e_AGE_19},
    {20, e_AGE_20},
    {21, e_AGE_21},
    {22, e_AGE_22},
    {23, e_AGE_23},
    {24, e_AGE_24},
    {25, e_AGE_25},
    {26, e_AGE_26},
    {27, e_AGE_27},
    {28, e_AGE_28},
    {29, e_AGE_29},
    {30, e_AGE_30},
    {31, e_AGE_31},
    {32, e_AGE_32},
    {33, e_AGE_33},
    {34, e_AGE_34},
    {35, e_AGE_35},
    {36, e_AGE_36},
    {37, e_AGE_37},
    {38, e_AGE_38},
    {39, e_AGE_39},
    {40, e_AGE_40},
};
static st_contact_t fs_contact_data[SIZE_CONTACT_DATA] = {0};
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int main()
{
    printf("cJSON Version: %s\n", cJSON_Version());

    process_contacts_json(PATH_FILE, fs_contact_data);
    show_contact(fs_contact_data);

    return 0;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
static long fs_get_file_size(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if (!fp)
        return -1;
    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fclose(fp);
        return -1;
    }
    long size = ftell(fp);
    fclose(fp);
    return size;
}

static int fs_read(const char *path, long offset, size_t size, unsigned char *buffer)
{
    FILE *fp = fopen(path, "rb");
    if (!fp)
        return -1;

    if (fseek(fp, offset, SEEK_SET) != 0)
    {
        fclose(fp);
        return -1;
    }

    size_t bytesRead = fread(buffer, 1, size, fp);
    fclose(fp);
    return (int)bytesRead;
}

static void process_contacts_json(const char* path_file, st_contact_t *fs_contact_data)
{
    int fs_file_size = fs_get_file_size(path_file);
    if (fs_file_size <= 0)
    {
        fprintf(stderr, "Failed to get file size or file is empty\n");
        return;
    }
    uint8_t *fs_read_buffer = (uint8_t *)malloc(fs_file_size + 1);
    if (!fs_read_buffer)
    {
        fprintf(stderr, "Failed to allocate memory for read buffer\n");
        return 0;
    }

    fs_read(PATH_FILE, 0, fs_file_size, fs_read_buffer);

    cJSON *root = cJSON_Parse(fs_read_buffer);
    if (!root)
    {
        printf("Fail parse JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    if (!cJSON_IsArray(root))
    {
        printf("JSON not array\n");
        cJSON_Delete(root);
        return;
    }

    int count = cJSON_GetArraySize(root);
    for (int i = 0; i < count && i < SIZE_CONTACT_DATA; ++i)
    {
        cJSON *item = cJSON_GetArrayItem(root, i);
        if (!cJSON_IsObject(item))
            continue;

        cJSON *name = cJSON_GetObjectItem(item, "Name");
        cJSON *age = cJSON_GetObjectItem(item, "Age");
        cJSON *address = cJSON_GetObjectItem(item, "Address");
        cJSON *online = cJSON_GetObjectItem(item, "Online");

        if (fs_contact_data != NULL)
        {
            if (cJSON_IsString(name))
            {
                strncpy(fs_contact_data[i].name, name->valuestring, BUF_SIZE_NAME - 1);
                fs_contact_data[i].name[BUF_SIZE_NAME - 1] = '\0';
            }
            if (cJSON_IsNumber(age))
            {
                int age_value = age->valueint;
                for (size_t j = 0; j < sizeof(fs_person_data) / sizeof(fs_person_data[0]); ++j)
                {
                    if (fs_person_data[j].age == age_value)
                    {
                        fs_contact_data[i].age_enum = fs_person_data[j].age_enum;
                        break;
                    }
                }
            }
            if (cJSON_IsString(address))
            {
                strncpy(fs_contact_data[i].address, address->valuestring, BUF_SIZE_ADDRESS - 1);
                fs_contact_data[i].address[BUF_SIZE_ADDRESS - 1] = '\0';
            }
            if (cJSON_IsBool(online))
            {
                fs_contact_data[i].is_online = cJSON_IsTrue(online);
            }
        }
    }

    cJSON_Delete(root);
    free(fs_read_buffer);
}

static void show_contact(st_contact_t *contact)
{
    if (!contact)
    {
        fprintf(stderr, "Invalid contact data\n");
        return;
    }

    for (size_t i = 0; i < SIZE_CONTACT_DATA; ++i)
    {
        if (strlen(contact[i].name) == 0) continue;
        printf("Contact #%d:\n", (int)i + 1);
        printf("  Name: %s\n", contact[i].name);
        printf("  Age: %d\n", contact[i].age_enum);
        printf("  Address: %s\n", contact[i].address);
        printf("  Online: %s\n", contact[i].is_online ? "Yes" : "No");
    }
}