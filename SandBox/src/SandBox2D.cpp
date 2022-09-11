
#include "SandBox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	:Layer("sandbox 2D"), m_CameraController(1280.f / 720.f)
{

}

void SandBox2D::OnAttach() 
{
	// 2022-9-9 codes moves to renderer2d
	//m_SquareVA = (KaluoEngine::VertexArray::Create());

	//float SqaureVertices[3 * 4] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.5f, 0.5f, 0.0f, 
	//	-0.5f, 0.5f, 0.0f
	//};

	//KaluoEngine::Ref<KaluoEngine::VertexBuffer> SquareVB;
	//SquareVB.reset(KaluoEngine::VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
	//KaluoEngine::BufferLayout SquareVBlayout{
	//	//takes in buffer elements initializer_list
	//	{ KaluoEngine::ShaderDataType::Float3, "a_Position" }
	//};
	//SquareVB->SetLayout(SquareVBlayout);
	//m_SquareVA->AddVertexBuffer(SquareVB);

	//unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	//KaluoEngine::Ref<KaluoEngine::IndexBuffer>SquareIndexBuffer;
	//SquareIndexBuffer.reset(KaluoEngine::IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
	//m_SquareVA->SetIndexBuffer(SquareIndexBuffer);

	//m_FlatColorShader = KaluoEngine::Shader::Create("assets/shaders/FlatColor.glsl");
	m_CheckerBoardTexture = KaluoEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}
void SandBox2D::OnDetach() 
{

}

void SandBox2D::OnUpdate(KaluoEngine::TimeStep timestep) 
{
	//2022-9-5 all camera stuffs move into camera controller
	m_CameraController.OnUpdate(timestep);

	//render stuffs
	KaluoEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	KaluoEngine::RenderCommand::Clear();

	//2022-9-4 2Drenderer class planning
	//KaluoEngine::Renderer::BeginScene(m_CameraController.GetCamera());
	KaluoEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	KaluoEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	KaluoEngine::Renderer2D::DrawQuad({ 0.5f, 0.0f }, { 0.5f, 0.15f }, { 0.2f, 0.3f, 0.8f, 1.0f });

	KaluoEngine::Renderer2D::DrawQuad({ 1.f, 0.0f, -0.1f }, { 1.5f, 1.5f }, m_CheckerBoardTexture);

	KaluoEngine::Renderer2D::EndScene();


	//2022-9-9 To do: Add: shader::setmat4, shader::Setfloat 4, so we dont need to do dynamic cast
	//2022-8-29 temporary cast the shader into openglshader and bind it
	//std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	//KaluoEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//KaluoEngine::Renderer::EndScene();
}
void SandBox2D::OnEvent(KaluoEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}
void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Kaluo Engine Info:");
	ImGui::Text("Hello World");

	//2022-8-29 
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}