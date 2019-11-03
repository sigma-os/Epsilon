#pragma once

#include <Epsilon/sigma_loader.h>
#include <Epsilon/uefi/protocol/graphics-output.h>
#include <Epsilon/lib.h>

void init_sigma_graphics();
void sigma_set_video_mode(uint64_t width, uint64_t height);
void* sigma_get_framebuffer();
size_t sigma_get_framebuffer_size();