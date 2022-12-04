#include "gpu/device.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

namespace mop {
namespace device {

    DLL_EXPORT void GetPlatform(platformProperties** result, int* number) {

        cl_uint platformNumber = 0;
        cl_platform_id platformIds[8];
        CL_CHECK_ERR(clGetPlatformIDs(8, platformIds, &platformNumber));

        *result = new platformProperties[platformNumber];
        *number = platformNumber;

        cl_device_type type;
        cl_uint value;
        size_t sizes[3];
        cl_ulong ulvalue;

        for (int i = 0; i < platformNumber; i++) {

            printf("platform idx : %d\n", i);
            result[i]->platform_id = platformIds[i];

            clGetPlatformInfo(
                (cl_platform_id)(result[i]->platform_id),
                CL_PLATFORM_VENDOR,
                256,
                result[i]->platform_vendor,
                NULL
            );
            printf("platform vendor : %s\n", result[i]->platform_vendor);

            clGetPlatformInfo(
                (cl_platform_id)(result[i]->platform_id),
                CL_PLATFORM_NAME,
                256,
                result[i]->platform_name,
                NULL
            );
            printf("platform name : %s\n", result[i]->platform_name);

            clGetPlatformInfo(
                (cl_platform_id)(result[i]->platform_id),
                CL_PLATFORM_VERSION,
                256,
                result[i]->platform_vertion,
                NULL
            );
            printf("platform version : %s\n", result[i]->platform_vertion);

            // デバイス取得
            cl_uint deviceNumber = 0;
            cl_device_id deviceIds[8];
            clGetDeviceIDs(
                (cl_platform_id)(result[i]->platform_id),
                CL_DEVICE_TYPE_ALL,
                8,
                deviceIds,
                &deviceNumber
            );

            result[i]->number_of_device = deviceNumber;

            for (int j = 0; j < deviceNumber; j++)
            {
                printf("    device idx : %d\n", j);
                result[i]->devices[j].device_id = (void*)(deviceIds[j]);

                clGetDeviceInfo(
                    (cl_device_id)(result[i]->devices[j].device_id),
                    CL_DEVICE_NAME,
                    256,
                    result[i]->devices[j].device_name,
                    NULL
                );
                printf("    device name : %s\n", result[i]->devices[j].device_name);

                clGetDeviceInfo(
                    (cl_device_id)(result[i]->devices[j].device_id),
                    CL_DEVICE_TYPE,
                    sizeof(cl_device_type),
                    &type,
                    NULL
                );
                result[i]->devices[j].is_gpu = type == CL_DEVICE_TYPE_GPU ? true : false;

                result[i]->devices[j].device_context =
                    (void*)clCreateContext(
                        NULL, 1,
                        (cl_device_id*)&(result[i]->devices[j].device_id),
                        NULL, NULL, NULL
                    );

                result[i]->devices[j].device_command_queue =
                    (void*)clCreateCommandQueue(
                        (cl_context)(result[i]->devices[j].device_context),
                        (cl_device_id)(result[i]->devices[j].device_id),
                        0, NULL
                    );

            }

        }

    }

    DLL_EXPORT void* CompileCLProgram(char* source_code, int code_size, deviceProperties* device) {

        cl_program result =
            clCreateProgramWithSource(
                (cl_context)(device->device_context),
                1,
                (const char**)&source_code,
                (const size_t*)&code_size,
                NULL
            );

        if (clBuildProgram(result, 1, (cl_device_id*)(&(device->device_id)), NULL, NULL, NULL)) {

            size_t logSize;

            clGetProgramBuildInfo(result, (cl_device_id)(device->device_id), CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);

            char* buildLog = (char*)malloc((logSize + 1));
            clGetProgramBuildInfo(result, (cl_device_id)(device->device_id), CL_PROGRAM_BUILD_LOG, logSize, buildLog, NULL);

            printf("%s\n", buildLog);
            free(buildLog);

        }

        return result;

    }

}
}
