#pragma once

#include <imgui/imgui.h>

#include "scene/Scene.h"
#include "scene/SceneManager.h"

// Components
#include "scene/components/TransformComponent.h"
#include "scene/components/MeshComponent.h"
#include "scene/components/CameraComponent.h"
#include "scene/components/AmbientLightComponent.h"

// Systems
#include "scene/systems/RenderSystem.h"
#include "scene/systems/CameraSystem.h"
#include "scene/systems/LightSystem.h"

#include "renderer/Shader.h"
#include "renderer/Renderer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/FrameBuffer.h"
#include "renderer/Texture.h"
#include "renderer/Skybox.h"
#include "renderer/Model.h"
#include "renderer/Mesh.h"
#include "renderer/Camera.h"
#include "renderer/light/DirectionalLight.h"
#include "renderer/light/AmbientLight.h"
#include "renderer/primitives/Quad.h"
#include "core/Window.h"
#include "core/Log.h"