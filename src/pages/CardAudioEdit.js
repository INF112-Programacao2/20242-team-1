'use client';
import React, { useState, useEffect } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import AudioInputPlayer from '../components/AudioInputPlayer';
import { Formik } from 'formik';
import * as Yup from 'yup';

const CarAudioEdit = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(true);
    const [data, setData] = useState(null); // Dados da API
    const [url, setURL] =useState(false);
    useEffect(() => {
        async function fetchData() {
            if (id) {
                try {
                    const response = await fetch(`http://localhost:3000/api/audio/${id}`);
                    const result = await response.json();
                    setURL(true);
                    setData(result); // Armazena os dados recebidos
                } catch (error) {
                    console.error('Erro ao buscar os dados:', error);
                } finally {
                    setLoading(false);
                }
            } else {
                setLoading(false);
            }
        }

        fetchData();
    }, [id]);

    if (loading) {
        return (
            <Container>
                <h2>Carregando...</h2>
            </Container>
        );
    }

    if (!data && id) {
        return (
            <Container>
                <h2>Nenhum dado encontrado</h2>
            </Container>
        );
    }

    const validationSchema = Yup.object({
        front: Yup.string()
            .required('A frente é obrigatória.')
            .min(3, 'O título deve ter pelo menos 3 caracteres.'),
        audio: Yup.mixed().required('O áudio é obrigatório.'),
    });

    return (
        <Container>
            <h2>Editar Cartão de Áudio</h2>
            <Formik
                enableReinitialize // Permite atualizar os valores iniciais dinamicamente
                initialValues={{
                    front: data?.front || '', // Pré-preenche com os dados do backend
                    audio:  data?.id || '', // O áudio será adicionado manualmente
                }}
                validationSchema={validationSchema}
                onSubmit={async (values, { setSubmitting }) => {
                    const formData = new FormData();
                    formData.append('front', values.front);
                    formData.append('deckId', id);
                    if (!url) {
                        formData.append('audio', values.audio, 'audio_recording.webm');
                    }

                    try {
                        const response = await fetch(`http://localhost:3000/api/audio`, {
                            method: 'POST',
                            body: formData,
                        });

                        if (!response.ok) {
                            throw new Error('Falha ao salvar o cartão de áudio');
                        }
                        window.location.reload();
                    } catch (error) {
                        console.error('Erro ao salvar o cartão:', error);
                    }
                    
                    setSubmitting(false);
                }}
            >
                {({
                    values,
                    errors,
                    touched,
                    handleChange,
                    handleBlur,
                    setFieldValue,
                    handleSubmit,
                    isSubmitting,
                }) => (
                    <Form onSubmit={handleSubmit}>
                        <Form.Group className="mb-3" controlId="formBasicTitle">
                            <Form.Label>Frente</Form.Label>
                            <Form.Control
                                type="text"
                                name="front"
                                placeholder="Adicione a frente do cartão"
                                value={values.front}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.front && !!errors.front}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.front}
                            </Form.Control.Feedback>
                        </Form.Group>

                        <Form.Group className="mb-3">
                            <Form.Label>Áudio</Form.Label>
                            <AudioInputPlayer
                                setAudio={(file) => setFieldValue('audio', file)}
                                responseAudio={data?.id ? `http://localhost:3000/dist/assets/uploads/${data.id}sound.webm`:null}
                            />
                            {touched.audio && errors.audio && (
                                <div className="text-danger">{errors.audio}</div>
                            )}
                        </Form.Group>

                        <Button variant="secondary" type="submit" size="lg" disabled={isSubmitting}>
                            {isSubmitting ? 'Salvando...' : 'Salvar'}
                        </Button>
                    </Form>
                )}
            </Formik>
        </Container>
    );
};

export default CarAudioEdit;
