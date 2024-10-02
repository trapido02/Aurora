#include "MainScene.h"

void MainScene::OnAttach(Aurora::Core::Window* window, Aurora::Renderer::Shader* shader, Aurora::Renderer::FrameBuffer* framebuffer)
{
	INFO("Scene attach");

	std::vector<std::string> cubemapPaths = {
		"resources/cubemaps/skybox/right.jpg",
		"resources/cubemaps/skybox/left.jpg",
		"resources/cubemaps/skybox/top.jpg",
		"resources/cubemaps/skybox/bottom.jpg",
		"resources/cubemaps/skybox/front.jpg",
		"resources/cubemaps/skybox/back.jpg"
	};

	m_SkyboxShader = new Aurora::Renderer::Shader("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");
	m_SkyboxShader->Create();
	m_SkyboxShader->SetUniform1i("skybox", 0);

	// Create camera
	m_Camera = m_Registry.create();
	m_Registry.emplace<Aurora::Scene::TransformComponent>(m_Camera);
	m_Registry.emplace<Aurora::Scene::CameraComponent>(m_Camera);

	auto& cameraTransform = m_Registry.get<Aurora::Scene::TransformComponent>(m_Camera);
	cameraTransform.position = glm::vec3{ 0.0f, 1.0f, 0.0f };

	Aurora::Renderer::Skybox* skybox = new Aurora::Renderer::Skybox(cubemapPaths);
	skybox->Create();

	auto& cameraComponent = m_Registry.get<Aurora::Scene::CameraComponent>(m_Camera);
	cameraComponent.skybox = skybox;
	cameraComponent.skyboxShader = m_SkyboxShader;

	// Create duck
	m_Duck = m_Registry.create();
	m_Registry.emplace<Aurora::Scene::TransformComponent>(m_Duck);
	m_Registry.emplace<Aurora::Scene::MeshComponent>(m_Duck, "resources/models/Duck.gltf");

	// Create baseplate
	m_Baseplate = m_Registry.create();
	m_Registry.emplace<Aurora::Scene::TransformComponent>(m_Baseplate);
	m_Registry.emplace<Aurora::Scene::MeshComponent>(m_Baseplate, "resources/models/baseplate.gltf");

	// Create ambient light
	m_AmbientLight = m_Registry.create();
	m_Registry.emplace<Aurora::Scene::AmbientLightComponent>(m_AmbientLight);

	// Create directional light
	m_DirectionalLight = m_Registry.create();
	m_Registry.emplace<Aurora::Scene::DirectionalLightComponent>(m_DirectionalLight);

	// Initalize systems
	m_CameraSystem.Init(m_Registry, window, shader, framebuffer);
	m_RenderSystem.Init(m_Registry, window, shader, framebuffer);
	m_LightSystem.Init(m_Registry, window, shader, framebuffer);
}

void MainScene::OnUpdate(Aurora::Core::Window* window, Aurora::Renderer::Shader* shader, Aurora::Renderer::FrameBuffer* framebuffer, float deltaTime)
{
	auto& cameraTransform = m_Registry.get<Aurora::Scene::TransformComponent>(m_Camera);

	// Create transformation matrix for the camera
	glm::mat4 transformationMatrix = glm::mat4(1.0f);

	transformationMatrix = glm::translate(transformationMatrix, cameraTransform.position);

	transformationMatrix = glm::rotate(transformationMatrix, cameraTransform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	transformationMatrix = glm::rotate(transformationMatrix, cameraTransform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, cameraTransform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	transformationMatrix = glm::scale(transformationMatrix, cameraTransform.size);

	// Get window size
	int windowWidth, windowHeight;
	window->GetSize(windowWidth, windowHeight);

	// Calculate direction vectors
	glm::vec3 forward = glm::normalize(glm::vec3(-transformationMatrix[2]));
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f))); // Calculate the cross product of the forward and the up vector

	//////////////////////////
	//     Process input    //
	//////////////////////////

	if (window->GetKeyDown(Aurora::Core::KEYCODE::F, true))
	{
		if (window->IsMouseLocked())
		{
			window->UnlockMouseCursor();
		}
		else
		{
			window->LockMouseCursor();
		}
	}

	glm::vec3 direction(0.0f);
	bool shouldMove = false;

	// Handle inputs and do all type of movements here
	if (window->GetKeyDown(Aurora::Core::KEYCODE::W))
	{
		direction += forward;
		shouldMove = true;
	}

	if (window->GetKeyDown(Aurora::Core::KEYCODE::S))
	{
		direction -= forward;
		shouldMove = true;
	}

	if (window->GetKeyDown(Aurora::Core::KEYCODE::A))
	{
		direction -= right;
		shouldMove = true;
	}

	if (window->GetKeyDown(Aurora::Core::KEYCODE::D))
	{
		direction += right;
		shouldMove = true;
	}

	if (shouldMove && (direction != glm::vec3(0.0f, 0.0f, 0.0f)))
	{
		glm::vec3 newPosition = glm::normalize(direction) * 5.0f * deltaTime;
		cameraTransform.position += newPosition;
	}

	//////////////////////////
	//     Process mouse    //
	//////////////////////////

	if (window->IsMouseLocked())
	{
		double mouseX, mouseY;
		window->GetMousePosition(mouseX, mouseY);

		float rotX = 50.0f * ((float)mouseY - ((float)windowHeight / 2.0f)) / (float)windowHeight;
		float rotY = 50.0f * ((float)mouseX - ((float)windowWidth / 2.0f)) / (float)windowWidth;

		glm::vec3 rotation = cameraTransform.rotation;

		rotation.x -= glm::radians(rotX);
		rotation.y -= glm::radians(rotY);

		if (rotation.x > glm::radians(89.0f))
			rotation.x = glm::radians(89.0f);
		if (rotation.x < glm::radians(-89.0f))
			rotation.x = glm::radians(-89.0f);

		if (rotation.y > glm::radians(180.0f))
			rotation.y = glm::radians(-180.0f);
		if (rotation.y < glm::radians(-180.0f))
			rotation.y = glm::radians(180.0f);

		cameraTransform.rotation = rotation;

		window->SetCursorPosition(((float)windowWidth / 2), ((float)windowHeight / 2));
	}

	m_LightSystem.Update(m_Registry, window, shader, framebuffer, deltaTime);
	m_RenderSystem.Update(m_Registry, window, shader, framebuffer, deltaTime);
	m_CameraSystem.Update(m_Registry, window, shader, framebuffer, deltaTime);
}

void MainScene::OnDetach(Aurora::Core::Window* window, Aurora::Renderer::Shader* shader, Aurora::Renderer::FrameBuffer* framebuffer)
{
	INFO("Scene detach");

	m_Registry.clear();

	m_CameraSystem.Exit(m_Registry, window, shader, framebuffer);
	m_RenderSystem.Exit(m_Registry, window, shader, framebuffer);
	m_LightSystem.Exit(m_Registry, window, shader, framebuffer);

	m_SkyboxShader->Destroy();
	delete m_SkyboxShader;
}