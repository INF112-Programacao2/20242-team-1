import React, { useState } from 'react';
import { ReactMic } from 'react-mic';
import Button from 'react-bootstrap/Button';
import { ReactComponent as MicIcon } from '../assets/icons/mic-fill.svg';
import { ReactComponent as PauseIcon } from '../assets/icons/pause-fill.svg';
import { ReactComponent as TrashIcon } from '../assets/icons/trash-fill.svg';

const AudioInputPlayer = ({ setAudio }) => {
    const [recording, setRecording] = useState(false);
    const [audioBlob, setAudioBlob] = useState(null);
    const [audioURL, setAudioURL] = useState(null);

    const startRecording = () => {
        setRecording(!recording)
    }
    const deleteRecording = () => {
        setAudioBlob(null);
        setAudioURL(null);
        setRecording(false);
        setAudio(null);
    };

    const onStop = (recordedBlob) => {
        setAudioBlob(recordedBlob.blob);
        const url = URL.createObjectURL(recordedBlob.blob);
        setAudioURL(url);
        setAudio(recordedBlob.blob);
    };

    return (
        <div className='player'>
            {!audioURL &&
                <Button variant="light" onClick={startRecording}>
                    {recording ? <PauseIcon /> : <MicIcon />}
                </Button>
            }
            {audioURL && !recording ?
                <>
                    <audio controls>
                        <source src={audioURL} type="audio/webm" />
                        Seu navegador não suporta o elemento de áudio.
                    </audio>
                    <Button variant="light" onClick={deleteRecording}>
                        <TrashIcon />
                    </Button>
                </>
                :
                <ReactMic
                    record={recording}
                    className="sound-wave audio"
                    onStop={onStop}
                    strokeColor="#000000"
                    backgroundColor="#f1f3f4"
                    mimeType="audio/webm"
                />
            }


        </div>
    );
};

export default AudioInputPlayer;
