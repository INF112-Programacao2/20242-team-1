'use client';
import React, { useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import AudioInputPlayer from '../components/AudioInputPlayer';
import { Formik } from 'formik';
import * as Yup from 'yup';
import { useNavigate } from "react-router-dom";


const CardAudioNew = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(false);
    const navigate = useNavigate();

    if (loading) {
        return (
            <Container>
                <h2>Loading...</h2>
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
            <h2>Novo Cartão de Áudio</h2>
            <Formik
                initialValues={{
                    front: '',
                    audio: null,
                }}
                validationSchema={validationSchema}
                onSubmit={async (values, { setSubmitting }) => {
                    const formData = new FormData();
                    formData.append('front', values.front);
                    formData.append('deckId', id);
                    formData.append('audio', values.audio, 'audio_recording.webm');
                    
                    try {
                        const response = await fetch(`http://localhost:3000/api/audio`, {
                            method: 'POST',
                            body: formData,
                        });

                        if (!response.ok) {
                            throw new Error('Falha ao salvar o cartão de áudio');
                        }
                        navigate(`/edit/deck/${id}`);
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

export default CardAudioNew;
