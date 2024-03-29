#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <string>
#include <algorithm>

#include "SvpSampleCom.h"
#ifdef USE_OPENCV
#include "cv_read_image.h"
#endif

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
#include "mpi_sys.h"
#endif

HI_U32 SvpSampleAlign(HI_U32 u32Size, HI_U32 u32AlignNum)
{
    return (u32Size + (u32AlignNum - u32Size%u32AlignNum)%u32AlignNum);
}

/*
* Malloc mem,depend on different environment
*/
HI_S32 SvpSampleMalloc(HI_CHAR *pchMmb, HI_CHAR *pchZone, HI_U64 *pu64PhyAddr, HI_VOID **ppvVirAddr, HI_U32 u32Size)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
    s32Ret = HI_MPI_SYS_MmzAlloc(pu64PhyAddr, ppvVirAddr, pchMmb, pchZone, u32Size);
#else
    *ppvVirAddr = (HI_VOID *)malloc(u32Size);
    if(HI_NULL == *ppvVirAddr)
    {
        s32Ret = HI_FAILURE;
    }
    else
    {
        *pu64PhyAddr = (HI_U64)*ppvVirAddr;
    }

#endif
    return s32Ret;
}

HI_S32 SvpSampleMallocMem(HI_CHAR *pchMmb, HI_CHAR *pchZone, HI_U32 u32Size, SVP_MEM_INFO_S *pstMem)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
    s32Ret = HI_MPI_SYS_MmzAlloc(&pstMem->u64PhyAddr, (void**)&pstMem->u64VirAddr, pchMmb, pchZone, u32Size);
    pstMem->u32Size = u32Size;
#else
    pstMem->u64VirAddr = (HI_U64)malloc(u32Size);
    if(0 == pstMem->u64VirAddr)
    {
        s32Ret = HI_FAILURE;
        pstMem->u64PhyAddr = 0;
        pstMem->u32Size    = 0;
    }
    else
    {
        pstMem->u64PhyAddr = pstMem->u64VirAddr;
        pstMem->u32Size    = u32Size;
    }
#endif
    return s32Ret;
}

/*
* Malloc mem with cache,depend on different environment
*/
HI_S32 SvpSampleMalloc_Cached(HI_CHAR *pchMmb, HI_CHAR *pchZone, HI_U64 *pu64PhyAddr, HI_VOID **ppvVirAddr, HI_U32 u32Size)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
    s32Ret = HI_MPI_SYS_MmzAlloc_Cached(pu64PhyAddr, ppvVirAddr, pchMmb, pchZone, u32Size);
#else
    *ppvVirAddr = (HI_U8 *)malloc(u32Size);
    if(HI_NULL == *ppvVirAddr)
    {
        s32Ret = HI_FAILURE;
    }
    else
    {
        *pu64PhyAddr = (HI_U64)(*ppvVirAddr);
    }
#endif
    return s32Ret;
}

HI_S32 SvpSampleMallocMemCached(HI_CHAR *pchMmb, HI_CHAR *pchZone, HI_U32 u32Size, SVP_MEM_INFO_S *pstMem)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
    s32Ret = HI_MPI_SYS_MmzAlloc_Cached(&pstMem->u64PhyAddr, (VOID**)&pstMem->u64VirAddr, pchMmb, pchZone, u32Size);
    pstMem->u32Size = u32Size;
#else
    pstMem->u64VirAddr = (HI_U64)malloc(u32Size);
    if(0 == pstMem->u64VirAddr)
    {
        s32Ret = HI_FAILURE;
        pstMem->u64PhyAddr = 0;
        pstMem->u32Size    = 0;
    }
    else
    {
        pstMem->u64PhyAddr = pstMem->u64VirAddr;
        pstMem->u32Size    = u32Size;
    }
#endif
    return s32Ret;
}

/*
 * Flush cache, if u32PhyAddr==0£¬that means flush all cache
*/
HI_S32 SvpSampleFlushCache(HI_U64 u64PhyAddr, HI_VOID *pvVirAddr, HI_U32 u32Size)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
    s32Ret = HI_MPI_SYS_MmzFlushCache(u64PhyAddr, pvVirAddr, u32Size);
#endif
    return s32Ret;
}

HI_S32 SvpSampleFlushMemCache(SVP_MEM_INFO_S *pstMem)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP
    s32Ret = HI_MPI_SYS_MmzFlushCache(pstMem->u64PhyAddr, (HI_VOID*)pstMem->u64VirAddr, u32Size);
#endif
    return s32Ret;
}

/*
* Free mem,depend on different environment
*/
HI_VOID SvpSampleFree(HI_U64 u64PhyAddr, HI_VOID *pvVirAddr)
{
#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP

    if ((0 != u64PhyAddr) && (NULL != pvVirAddr))
    {
        (HI_VOID)HI_MPI_SYS_MmzFree(u64PhyAddr, pvVirAddr);
    }
#else
    if (NULL != pvVirAddr)
    {
        free(pvVirAddr);
        pvVirAddr = NULL;
    }
#endif
}


HI_VOID SvpSampleMemFree(SVP_MEM_INFO_S *pstMem)
{
#if ((defined __arm__) || (defined __aarch64__)) && defined HISI_CHIP

    if ((0 != pstMem->u64PhyAddr) && (0 != pstMem->u64VirAddr))
    {
        (HI_VOID)HI_MPI_SYS_MmzFree(pstMem->u64PhyAddr, (HI_VOID*)(HI_UL)pstMem->u64VirAddr);
    }
#else
    if (0 != pstMem->u64VirAddr)
    {
        free((void*)pstMem->u64VirAddr);
        pstMem->u64VirAddr = 0;
    }
#endif
}

/*
*Open file,depend on different environment
*/
FILE* SvpSampleOpenFile(const HI_CHAR *pchFileName, const HI_CHAR *pchMode)
{
    FILE *fp = NULL;
#ifdef _MSC_VER
    errno_t errno;
    errno = fopen_s(&fp, pchFileName, pchMode);
    if (0 != errno)
    {
        printf("Error(%d): %s, read file(%s).\n", errno, strerror(errno), pchFileName);
    }
#else
    fp = fopen(pchFileName, pchMode);
#endif

    return fp;
}

/*
*Close file
*/
HI_VOID SvpSampleCloseFile(FILE *fp)
{
    if(fp)
    {
        fclose(fp);
        fp = NULL;
    }
}

HI_S32 SvpSampleMallocBlob(SVP_BLOB_S *pstBlob, SVP_BLOB_TYPE_E enType, HI_U32 u32Num, HI_U32 u32Chn,
    HI_U32 u32Width, HI_U32 u32Height, HI_U32 u32UsrAlign)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ElemByte = 1;
    HI_U32 u32Size  = 0;
    HI_U32 u32Stride;

    CHECK_EXP_RET(u32Num==0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Num(%d) must be greater than 0", u32Num);
    CHECK_EXP_RET(u32Width==0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Width(%d) must be greater than 0", u32Width);
    CHECK_EXP_RET(u32Height==0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Height(%d) must be greater than 0", u32Height);

    pstBlob->enType  = enType;
    pstBlob->u32Num    = u32Num;

    switch(enType)
    {
    case SVP_BLOB_TYPE_S32:
    {
        CHECK_EXP_RET(u32Chn == 0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Chn(%d) must be greater than 0", u32Chn);
        pstBlob->unShape.stWhc.u32Chn = u32Chn;
        pstBlob->unShape.stWhc.u32Height = u32Height;
        pstBlob->unShape.stWhc.u32Width = u32Width;
        u32ElemByte = 4; // SQ20.12
        u32Stride = SvpSampleAlign(u32Width * u32ElemByte, u32UsrAlign);
        pstBlob->u32Stride = u32Stride;
        u32Size = u32Num * u32Chn * u32Stride * u32Height;
        break;
    }
    case SVP_BLOB_TYPE_U8:
    {
        CHECK_EXP_RET(u32Chn == 0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Chn(%d) must be greater than 0", u32Chn);
        pstBlob->unShape.stWhc.u32Chn = u32Chn;
        pstBlob->unShape.stWhc.u32Height = u32Height;
        pstBlob->unShape.stWhc.u32Width = u32Width;
        u32ElemByte = 1;
        u32Stride = SvpSampleAlign(u32Width * u32ElemByte, u32UsrAlign);
        pstBlob->u32Stride = u32Stride;
        u32Size = u32Num * u32Chn * u32Stride * u32Height;
        break;
    }
    case SVP_BLOB_TYPE_YVU420SP:
    {
        pstBlob->unShape.stWhc.u32Chn = 3;
        pstBlob->unShape.stWhc.u32Height = u32Height;
        pstBlob->unShape.stWhc.u32Width = u32Width;
        u32ElemByte = 1;
        u32Stride = SvpSampleAlign(u32Width * u32ElemByte, u32UsrAlign);
        pstBlob->u32Stride = u32Stride;
        u32Size = u32Num * u32Chn * u32Stride * u32Height * 3 / 2;
        break;
    }
    case SVP_BLOB_TYPE_YVU422SP:
    {
        pstBlob->unShape.stWhc.u32Chn = 3;
        pstBlob->unShape.stWhc.u32Height = u32Height;
        pstBlob->unShape.stWhc.u32Width = u32Width;
        u32ElemByte = 1;
        u32Stride = SvpSampleAlign(u32Width * u32ElemByte, u32UsrAlign);
        pstBlob->u32Stride = u32Stride;
        u32Size = u32Num * u32Chn * u32Stride * u32Height * 2;
        break;
    }
    case SVP_BLOB_TYPE_VEC_S32:
    {
        pstBlob->unShape.stWhc.u32Chn = 1;
        pstBlob->unShape.stWhc.u32Height = u32Height;
        pstBlob->unShape.stWhc.u32Width = u32Width;
        u32ElemByte = 4;
        u32Stride = SvpSampleAlign(u32Width * u32ElemByte, u32UsrAlign);
        pstBlob->u32Stride = u32Stride;
        u32Size = u32Num * u32Chn * u32Stride * u32Height;
        break;
    }
    case SVP_BLOB_TYPE_SEQ_S32:
    {
        //pstBlob->u32Num = u32Num;
        //pstBlob->unShape.stSeq.u32Dim = u32Width;
        //pstBlob->unShape.stSeq.u64VirAddrStep = (HI_U64)pstCtx->pu32Seqs;
        //u32ElemByte = 4;
        //u32Stride = SvpSampleAlign(u32Width * u32ElemByte, STRIDE_ALIGN);
        //pstBlob->u32Stride = u32Stride;
        //u32Size = pstCtx->u32SeqNr * u32Chn * u32Stride * u32Height * pstCtx->u32TotalT;

        printf("enType SEQ_S32 should invoke SvpSampleMallocSeqBlob!\n");
        return HI_FAILURE;
    }
    default:
    {
        CHECK_EXP_RET(1, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "enType(%d) out of range [%d, %d)", enType,
            SVP_BLOB_TYPE_S32, SVP_BLOB_TYPE_BUTT);
        break;
    }
    }

    s32Ret = SvpSampleMalloc(NULL, NULL, &pstBlob->u64PhyAddr, (HI_VOID**)&pstBlob->u64VirAddr, u32Size);
    CHECK_EXP_RET(HI_SUCCESS!=s32Ret, s32Ret, "malloc blob mem failed!");

    return s32Ret;
}

HI_S32 SvpSampleMallocSeqBlob(SVP_BLOB_S *pstBlob, SVP_BLOB_TYPE_E enType, HI_U32 u32Num, HI_U32 u32Dim, SVP_SAMPLE_LSTMRunTimeCtx *pstCtx)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ElemByte = 4;
    HI_U32 u32Size = 0, i = 0, u32TotalT;
    HI_U32 u32Stride;
    HI_U32 *pu32VirStep = NULL;

    CHECK_EXP_RET(u32Num == 0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Num(%d) must be greater than 0", u32Num);
    CHECK_EXP_RET(u32Dim == 0, HI_ERR_SVP_NNIE_ILLEGAL_PARAM, "u32Dim(%d) must be greater than 0", u32Dim);
    CHECK_EXP_RET(enType != SVP_BLOB_TYPE_SEQ_S32, HI_ERR_SVP_NNIE_ILLEGAL_PARAM,
        "enType(%d) should be SEQ_S32(%d)", enType, SVP_BLOB_TYPE_SEQ_S32);

    pstBlob->enType = enType;
    pstBlob->u32Num = u32Num;

    pu32VirStep = (HI_U32 *)pstCtx->pu32Seqs;
    pstBlob->unShape.stSeq.u32Dim = u32Dim;
    pstBlob->unShape.stSeq.u64VirAddrStep = (HI_U64)pstCtx->pu32Seqs;
    u32ElemByte = 4;
    u32Stride = SvpSampleAlign(u32Dim * u32ElemByte, STRIDE_ALIGN);
    pstBlob->u32Stride = u32Stride;
    u32TotalT = 0;
    for (i = 0;i < pstBlob->u32Num;i++)
    {
        u32TotalT += pu32VirStep[i];
    }
    u32Size = u32Stride * u32TotalT;

    s32Ret = SvpSampleMalloc(NULL, NULL, &pstBlob->u64PhyAddr, (HI_VOID**)&pstBlob->u64VirAddr, u32Size);
    CHECK_EXP_RET(HI_SUCCESS != s32Ret, s32Ret, "malloc blob mem failed!");

    return s32Ret;
}

HI_VOID SvpSampleFreeBlob(SVP_BLOB_S *pstBlob)
{
    SvpSampleFree((pstBlob->u64PhyAddr), (HI_VOID*)(pstBlob->u64VirAddr));
    memset(pstBlob, 0, sizeof(*pstBlob));
}

HI_S32 SvpSampleMallocRPNBlob(SVP_BLOB_S *pstBlob, HI_U32 u32Size, HI_U32 u32UsrStride)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ElemByte = 4;
    HI_U32 rpnCoordi = 4;

    pstBlob->enType = SVP_BLOB_TYPE_S32;
    pstBlob->u32Num = 1;
    pstBlob->unShape.stWhc.u32Chn = 1;
    pstBlob->unShape.stWhc.u32Height = u32Size;
    pstBlob->unShape.stWhc.u32Width = 4;
    pstBlob->u32Stride = SvpSampleAlign(pstBlob->unShape.stWhc.u32Width * u32ElemByte, u32UsrStride);

    // RPN memory
    s32Ret = SvpSampleMalloc(NULL, NULL, &pstBlob->u64PhyAddr, (HI_VOID**)&pstBlob->u64VirAddr, u32Size * rpnCoordi * u32ElemByte);
    CHECK_EXP_RET(HI_SUCCESS != s32Ret, s32Ret, "malloc blob mem failed!");

    // indicator memory
   /* s32Ret = SvpSampleMalloc(NULL, NULL, &pstBlob->u64VirAddr, (HI_VOID**)&pstBlob->u64VirAddr, u32Size * u32ElemByte);
    CHECK_EXP_RET(HI_SUCCESS != s32Ret, s32Ret, "malloc blob mem failed!");*/


    return s32Ret;

}

void SvpSampleFreeRPNBlob(SVP_BLOB_S *pstBlob)
{
    SvpSampleFree((pstBlob->u64PhyAddr), (HI_VOID*)(pstBlob->u64PhyAddr));
    SvpSampleFree((pstBlob->u64VirAddr), (HI_VOID*)(pstBlob->u64VirAddr));
    memset(pstBlob, 0, sizeof(*pstBlob));
}

HI_S32 SvpSampleReadAllSrcImg(FILE *afp[], SVP_SRC_BLOB_S astSrcBlobs[],
    HI_U32 u32SrcNum, vector<SVP_SAMPLE_FILE_NAME_PAIR>& imgNameRecoder)
{
    HI_S32 s32Ret = HI_SUCCESS;

    imgNameRecoder.clear();

    for (HI_U32 j = 0; j < u32SrcNum; j++)
    {
        vector<SVP_SAMPLE_FILE_NAME_PAIR> imgNameRecoder_temp;

        if (astSrcBlobs[j].enType >= 0 && astSrcBlobs[j].enType < SVP_BLOB_TYPE_BUTT)
        {
            FILE *fp = afp[j];
            s32Ret = SvpSampleImgReadFromImglist(fp, &astSrcBlobs[j], 0, imgNameRecoder_temp);
            CHECK_EXP_RET(HI_SUCCESS != s32Ret, s32Ret, "SvpSampleImgReadFromImglist failed");
        }

        /* get image name only from src[0] image list */
        if (0 == j) {
            imgNameRecoder = imgNameRecoder_temp;
        }
    }
    return s32Ret;
}

SVP_SAMPLE_FILE_NAME_PAIR SvpSampleGetFileNameFromPath(std::string strImgPath)
{
    std::string strFileNameFull;
    std::string strBasic;
    std::string strSuffix;
    SVP_SAMPLE_FILE_NAME_PAIR namePair;

    size_t fileNamePos = strImgPath.find_last_of("/");
    /*  "/" not found and set pos to 0 */
    if (fileNamePos == std::string::npos) {
        fileNamePos = 0;
        strFileNameFull = strImgPath;
    }
    else {
        strFileNameFull = strImgPath.substr(fileNamePos + 1);
    }

    size_t suffixPos = strFileNameFull.find_last_of(".");
    if (suffixPos != std::string::npos) {
        strSuffix = strFileNameFull.substr(suffixPos + 1);
    }

    strBasic = strFileNameFull.substr(0, suffixPos);

    namePair.first = strBasic;
    namePair.second = strSuffix;
    return namePair;
}

HI_S32 SvpSampleImgReadFromImglist(FILE *fp, SVP_BLOB_S *pstBlob,
    HI_U32 u32StartLine, vector<SVP_SAMPLE_FILE_NAME_PAIR>& imgNameRecoder)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i, j, c, h;
    FILE *imgFp = NULL;
    HI_U32 u32ElemSize = 1;
    imgNameRecoder.clear();

    CHECK_EXP_RET(!fp, HI_ERR_SVP_NNIE_NULL_PTR, "fp is null");
    CHECK_EXP_RET(!pstBlob, HI_ERR_SVP_NNIE_NULL_PTR, "pstBlob is null");

    HI_U8 *pu8Ptr = (HI_U8*)pstBlob->u64VirAddr;
    fseek(fp, 0, SEEK_SET);

    for (i = 0;i < u32StartLine; i++)
    {
        HI_CHAR aszImg[SVP_SAMPLE_MAX_PATH] = { '\0' };
#ifdef _MSC_VER
        FSCANF_S(fp, "%s", aszImg, SVP_SAMPLE_MAX_PATH);
#else
        FSCANF_S(fp, "%s", aszImg);
#endif
    }

    switch (pstBlob->enType)
    {
        case SVP_BLOB_TYPE_S32:
        case SVP_BLOB_TYPE_VEC_S32:
        {
            HI_BOOL bFailFlag = HI_FALSE;
            u32ElemSize = sizeof(HI_S32);
            for (i = u32StartLine, j = 0; j < pstBlob->u32Num; i++, j++)
            {
                HI_CHAR aszImg[SVP_SAMPLE_MAX_PATH] = { '\0' };

#ifdef _MSC_VER
                FSCANF_S(fp, "%s", aszImg, SVP_SAMPLE_MAX_PATH);
#else
                FSCANF_S(fp, "%s", aszImg);
#endif
                imgNameRecoder.push_back(SvpSampleGetFileNameFromPath(string(aszImg)));

                imgFp = SvpSampleOpenFile(aszImg, "rb");
                CHECK_EXP_RET(!imgFp, HI_FAILURE, "open file(%s) failed!", aszImg);

                for (c = 0; c < pstBlob->unShape.stWhc.u32Chn; c++)
                {
                    for (h = 0; h < pstBlob->unShape.stWhc.u32Height; h++)
                    {
                        s32Ret = (HI_S32)fread(pu8Ptr, pstBlob->unShape.stWhc.u32Width * u32ElemSize, 1, imgFp);
                        if (1 != s32Ret)
                        {
                            bFailFlag = HI_TRUE;
                            printf("fread failed, (n,c,h)=(%d,%d,%d)!", i, c, h);
                            goto Fail1;
                        }
                        pu8Ptr += pstBlob->u32Stride;
                    }
                }
                fclose(imgFp);
            }
        Fail1:
            if (bFailFlag)
            {
                fclose(imgFp);
                return HI_FAILURE;
            }
        break;
        }
        case SVP_BLOB_TYPE_U8:
        {
            HI_BOOL bFailFlag = HI_FALSE;
            u32ElemSize = sizeof(HI_U8);
            for (i = u32StartLine, j = 0; j < pstBlob->u32Num; i++, j++)
            {
                HI_CHAR aszImg[SVP_SAMPLE_MAX_PATH] = { '\0' };

#ifdef _MSC_VER
                FSCANF_S(fp, "%s", aszImg, SVP_SAMPLE_MAX_PATH);
#else
                FSCANF_S(fp, "%s", aszImg);
#endif
                SVP_SAMPLE_FILE_NAME_PAIR filename = SvpSampleGetFileNameFromPath(string(aszImg));
                imgNameRecoder.push_back(filename);

#ifdef USE_OPENCV
                HI_BOOL bIsRawImg = HI_TRUE;

                std::string strSuffix = filename.second;
                transform(strSuffix.begin(), strSuffix.end(), strSuffix.begin(), ::tolower);

                if (strSuffix == "jpg" || strSuffix == "jpeg"
                    || strSuffix == "png" || strSuffix == "bmp")
                {
                    SVPUtils_ReadImage(aszImg, pstBlob, &pu8Ptr);
                    bIsRawImg = HI_FALSE;
                }

                if (bIsRawImg)
#endif
                {
                    imgFp = SvpSampleOpenFile(aszImg, "rb");
                    CHECK_EXP_RET(!imgFp, HI_FAILURE, "open file(%s) failed!", aszImg);

                    for (c = 0; c < pstBlob->unShape.stWhc.u32Chn; c++)
                    {
                        for (h = 0; h < pstBlob->unShape.stWhc.u32Height; h++)
                        {
                            s32Ret = (HI_S32)fread(pu8Ptr, pstBlob->unShape.stWhc.u32Width * u32ElemSize, 1, imgFp);
                            if (1 != s32Ret)
                            {
                                bFailFlag = HI_TRUE;
                                printf("fread failed, (n,c,h)=(%d,%d,%d)!", i, c, h);
                                goto Fail2;
                            }
                            pu8Ptr += pstBlob->u32Stride;
                        }
                    }
                    fclose(imgFp);
                }
            }
        Fail2:
            if (bFailFlag)
            {
                fclose(imgFp);
                return HI_FAILURE;
            }
            break;
        }
        case SVP_BLOB_TYPE_YVU420SP:
        {
            HI_BOOL bFailFlag = HI_FALSE;
            u32ElemSize = sizeof(HI_U8);;
            for (i = u32StartLine, j = 0; j < pstBlob->u32Num; i++, j++)
            {
                HI_CHAR aszImg[SVP_SAMPLE_MAX_PATH] = { '\0' };

#ifdef _MSC_VER
                FSCANF_S(fp, "%s", aszImg, SVP_SAMPLE_MAX_PATH);
#else
                FSCANF_S(fp, "%s", aszImg);
#endif

                imgNameRecoder.push_back(SvpSampleGetFileNameFromPath(string(aszImg)));

                imgFp = SvpSampleOpenFile(aszImg, "rb");
                CHECK_EXP_RET(!imgFp, HI_FAILURE, "open file(%s) failed!", aszImg);
                CHECK_EXP_RET(pstBlob->unShape.stWhc.u32Chn != 3, HI_ERR_SVP_NNIE_ILLEGAL_PARAM,
                    "entype(%d)'s blob chn(%d) should be 3", pstBlob->enType, pstBlob->unShape.stWhc.u32Chn);

                for (h = 0; h < pstBlob->unShape.stWhc.u32Height * 3 / 2; h++)
                {
                    s32Ret = (HI_S32)fread(pu8Ptr, pstBlob->unShape.stWhc.u32Width * u32ElemSize, 1, imgFp);
                    if (1 != s32Ret)
                    {
                        bFailFlag = HI_TRUE;
                        printf("fread failed, (n,h)=(%d,%d)!", i, h);
                        goto Fail3;
                    }
                    pu8Ptr += pstBlob->u32Stride;
                }
            }
        Fail3:
            if (bFailFlag)
            {
                fclose(imgFp);
                return HI_FAILURE;
            }
            break;
        }
        case SVP_BLOB_TYPE_YVU422SP:
        {
            HI_BOOL bFailFlag = HI_FALSE;
            u32ElemSize = sizeof(HI_U8);
            for (i = u32StartLine, j = 0; j < pstBlob->u32Num; i++, j++)
            {
                HI_CHAR aszImg[SVP_SAMPLE_MAX_PATH] = { '\0' };

#ifdef _MSC_VER
                FSCANF_S(fp, "%s", aszImg, SVP_SAMPLE_MAX_PATH);
#else
                FSCANF_S(fp, "%s", aszImg);
#endif

                imgNameRecoder.push_back(SvpSampleGetFileNameFromPath(string(aszImg)));

                imgFp = SvpSampleOpenFile(aszImg, "rb");
                CHECK_EXP_RET(!imgFp, HI_FAILURE, "open file(%s) failed!", aszImg);
                CHECK_EXP_RET(pstBlob->unShape.stWhc.u32Chn != 3, HI_ERR_SVP_NNIE_ILLEGAL_PARAM,
                    "entype(%d)'s blob chn(%d) should be 3", pstBlob->enType, pstBlob->unShape.stWhc.u32Chn);

                for (h = 0; h < pstBlob->unShape.stWhc.u32Height * 2; h++)
                {
                    s32Ret = (HI_S32)fread(pu8Ptr, pstBlob->unShape.stWhc.u32Width * u32ElemSize, 1, imgFp);
                    if (1 != s32Ret)
                    {
                        bFailFlag = HI_TRUE;
                        printf("fread failed, (n,h)=(%d,%d)!", i, h);
                        goto Fail4;
                    }
                    pu8Ptr += pstBlob->u32Stride;
                }
            }
        Fail4:
            if (bFailFlag)
            {
                fclose(imgFp);
                return HI_FAILURE;
            }
            break;
        }
        case SVP_BLOB_TYPE_SEQ_S32:
        {
            HI_BOOL bFailFlag = HI_FALSE;
            u32ElemSize = sizeof(HI_S32);
            for (i = u32StartLine, j = 0; j < pstBlob->u32Num; i++, j++)
            {
                HI_CHAR aszImg[SVP_SAMPLE_MAX_PATH] = { '\0' };
                HI_U32  *pu32TimeStep = (HI_U32*)pstBlob->unShape.stSeq.u64VirAddrStep;

#ifdef _MSC_VER
                FSCANF_S(fp, "%s", aszImg, SVP_SAMPLE_MAX_PATH);
#else
                FSCANF_S(fp, "%s", aszImg);
#endif

                imgNameRecoder.push_back(SvpSampleGetFileNameFromPath(string(aszImg)));

                imgFp = SvpSampleOpenFile(aszImg, "rb");
                CHECK_EXP_RET(!imgFp, HI_FAILURE, "open file(%s) failed!", aszImg);

                for (h = 0; h < pu32TimeStep[i]; h++)
                {
                    s32Ret = (HI_S32)fread(pu8Ptr, pstBlob->unShape.stSeq.u32Dim * u32ElemSize, 1, imgFp);
                    if (1 != s32Ret)
                    {
                        bFailFlag = HI_TRUE;
                        printf("fread failed, (n,h)=(%d,%d)!", i, h);
                        goto Fail5;
                    }
                    pu8Ptr += pstBlob->u32Stride;
                }
            }
        Fail5:
            if (bFailFlag)
            {
                fclose(imgFp);
                return HI_FAILURE;
            }
            break;
        }
        default:
        {
            printf("enType(%d) out of range {U8(%d), YVU420SP(%d), YVU422SP(%d)}",
                pstBlob->enType, SVP_BLOB_TYPE_U8, SVP_BLOB_TYPE_YVU420SP, SVP_BLOB_TYPE_YVU420SP);
            return HI_ERR_SVP_NNIE_ILLEGAL_PARAM;
        }
    }

    return HI_SUCCESS;
}
