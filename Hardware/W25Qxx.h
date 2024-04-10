#ifndef __W25Qxx_H
#define __W25Qxx_H

void W25Qxx_Init(void);
void W25Qxx_PageProgram(uint32_t Addr,uint8_t *DataArray,uint16_t Count);
void W25Qxx_SectorErase4KB(uint32_t Addr);
void W25Qxx_ReadID(uint8_t *MID,uint16_t *DID);
void W25Qxx_ReadData(uint32_t Addr,uint8_t *DataArray,uint32_t Count);

#endif
